#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../Other/CameraActor.h"
#include"../../Field/FieldBase.h"
#include"../../Graphic/AnimLoader.h"
#include"../../Graphic/Sprite.h"
#include"../../ID/EnumIDs.h"
#include"../../Define.h"
#include"../Other/CameraActor.h"
#include"../../Fade/FadeSprite.h"
#include"../../Sound/Sound.h"

Player::Player(IWorld* world, const Vector3& position, const IBodyPtr& body):
	Actor(world,"Player",position,body),animation_(),
	floatPower_(MaxFloatPower), wind_()
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {update_Idle(deltaTime); };
	playerToNextModeFunc_[Player_State::Idle]= [this]() {to_Idle(); };
	playerEndModeFunc_[Player_State::Idle]= [this]() {end_Idle(); };

	playerUpdateFunc_[Player_State::Slide] = [this](float deltaTime) {update_Slide(deltaTime); };
	playerToNextModeFunc_[Player_State::Slide] = [this]() {to_Slide(); };
	playerEndModeFunc_[Player_State::Slide] = [this]() {end_Slide(); };
	
	playerUpdateFunc_[Player_State::Jump] = [this](float deltaTime) {update_Jump(deltaTime); };
	playerToNextModeFunc_[Player_State::Jump] = [this]() {to_Jump(); };
	playerEndModeFunc_[Player_State::Jump] = [this]() {end_Jump(); };
	
	playerUpdateFunc_[Player_State::SlideJump] = [this](float deltaTime) {update_SlideJump(deltaTime); };
	playerToNextModeFunc_[Player_State::SlideJump] = [this]() {to_SlideJump(); };
	playerEndModeFunc_[Player_State::SlideJump] = [this]() {end_SlideJump(); };

	playerUpdateFunc_[Player_State::Float] = [this](float deltaTime) {update_Float(deltaTime); };
	playerToNextModeFunc_[Player_State::Float] = [this]() {to_Float(); };
	playerEndModeFunc_[Player_State::Float] = [this]() {end_Float(); };

	playerUpdateFunc_[Player_State::Fly] = [this](float deltaTime) {update_Fly(deltaTime); };
	playerToNextModeFunc_[Player_State::Fly] = [this]() {to_Fly(); };
	playerEndModeFunc_[Player_State::Fly] = [this]() {end_Fly(); };

	playerUpdateFunc_[Player_State::WallRun] = [this](float deltaTime) {update_WallRun(deltaTime); };
	playerToNextModeFunc_[Player_State::WallRun] = [this]() {to_WallRun(); };
	playerEndModeFunc_[Player_State::WallRun] = [this]() {end_WallRun(); };

	playerUpdateFunc_[Player_State::FloatJump] = [this](float deltaTime) {update_FloatJump(deltaTime); };
	playerToNextModeFunc_[Player_State::FloatJump] = [this]() {to_FloatJump(); };
	playerEndModeFunc_[Player_State::FloatJump] = [this]() {end_FloatJump(); };

	playerUpdateFunc_[Player_State::FloatFall] = [this](float deltaTime) {update_FloatFall(deltaTime); };
	playerToNextModeFunc_[Player_State::FloatFall] = [this]() {to_FloatFall(); };
	playerEndModeFunc_[Player_State::FloatFall] = [this]() {end_FloatFall(); };

	playerUpdateFunc_[Player_State::Fall] = [this](float deltaTime) {update_Fall(deltaTime); };
	playerToNextModeFunc_[Player_State::Fall] = [this]() {to_Fall(); };
	playerEndModeFunc_[Player_State::Fall] = [this]() {end_Fall(); };

	playerUpdateFunc_[Player_State::Blow] = [this](float deltaTime) {update_Blow(deltaTime); };
	playerToNextModeFunc_[Player_State::Blow] = [this]() {to_Blow(); };
	playerEndModeFunc_[Player_State::Blow] = [this]() {end_Blow(); };

	playerUpdateFunc_[Player_State::Down] = [this](float deltaTime) {update_Down(deltaTime); };
	playerToNextModeFunc_[Player_State::Down] = [this]() {to_Down(); };
	playerEndModeFunc_[Player_State::Down] = [this]() {end_Down(); };

	playerUpdateFunc_[Player_State::GetUp] = [this](float deltaTime) {update_GetUp(deltaTime); };
	playerToNextModeFunc_[Player_State::GetUp] = [this]() {to_GetUp(); };
	playerEndModeFunc_[Player_State::GetUp] = [this]() {end_GetUp(); };

	playerUpdateFunc_[Player_State::OutOfField] = [this](float deltaTime) {update_OutOfField(deltaTime); };
	playerToNextModeFunc_[Player_State::OutOfField] = [this]() {to_OutOfField(); };
	playerEndModeFunc_[Player_State::OutOfField] = [this]() {end_OutOfField(); };

}

void Player::initialize()
{
	state_ = Player_State::Idle;
	gravity_ = 0.0f;
	prevfloor_ = false;
	blowDirection_ = Vector3::Zero;
}

void Player::update(float deltaTime)
{
	playerUpdateFunc_[state_](deltaTime);

	animation_.Update(MathHelper::Sign(deltaTime)*0.5f);

	position_ += velocity_;
	velocity_ *= velocityMultPower;

	velocityMultPower = DefVelocityMult;//velocityの乗算割合を元に戻す

	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result))position_ = result;
	//床との接地判定
	if (floor(result)) {
		prevfloor_ = true;
		position_ = result+rotation_.Up()*(body_->length()*0.5f+body_->radius());
	}
	else prevfloor_ = false;

	if (state_ == Player_State::OutOfField)return;//既に範囲外状態なら範囲外検索はしない
	Vector3 hitcenter;
	if (world_->getField()->getOutMesh().collide_capsule(position_ + rotation_.Up()*(body_->length()*0.5f), position_ + rotation_.Down()*(body_->length()*0.5f), body_->radius(), (VECTOR*)&hitcenter)) {
		change_State(Player_State::OutOfField);
	}
}

void Player::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f);
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
	body_->transform(getPose())->draw();

	wind_.draw();

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "%f:%f:%f", position_.x, position_.y, position_.z);

	Vector2 gaugeDrawPos{ 100.0f,100.0f };
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_FLOATGAUGE_FRAME, gaugeDrawPos, Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_FLOATGAUGE_FRAME))*0.5f, Vector2::One);
	SetDrawBright(220, 0, 140);
	DrawCircleGauge(gaugeDrawPos.x, gaugeDrawPos.y, floatPower_, Sprite::GetInstance().GetHandle(SPRITE_ID::SPRITE_FLOATGAUGE));
	SetDrawBright(255, 255, 255);
	DebugDraw::DebugDrawFormatString(200, 300, GetColor(255, 255, 255), "%f,%f,%f", position_.x, position_.y, position_.z);
}

void Player::aerialVelocityKeep()
{
	velocityMultPower = 0.95f;


}

void Player::floatVelocityKeep()
{
}

void Player::hit(const Vector3& direction,bool forceHit)
{
	blowDirection_ = Vector3(direction).Normalize();
	if (forceHit)velocity_ += blowDirection_;//強制ヒットなら押し出し

	if (!isCanDown())return;//ヒット条件を満たしてなければ
	
	blowDirection_ += Vector3::Up*0.2f;//吹っ飛ばし移行時は少し打ち上げる

	change_State_and_Anim(Player_State::Blow, Player_Animation::Blow, 0.0f, 1.0f, false);

}

void Player::receiveMessage(EventMessage message, void * param)
{
	switch (message)
	{
	case EventMessage::Hit_Car:
		hit(*(Vector3*)param,true);
	case EventMessage::Hit_Bullet:
		hit(*(Vector3*)param);
		break;
	default:
		break;
	}
}

bool Player::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop)
{
	//同じ状態には遷移しない
	if (state_ == state)return false;
	//先にアニメーションを切り替え
	change_Animation(animID, animFrame, animSpeed, isLoop);

	if (!change_State(state))return false;

	return true;
}

bool Player::change_State(Player_State state)
{
	//状態が変わらないなら失敗
	if (state_ == state)return false;

	//状態の終了処理を行う
	playerEndModeFunc_[state_]();
	//状態を更新
	state_ = state;
	//状態変更を行う
	playerToNextModeFunc_[state_]();
	//更新成功
	return true;
}

void Player::change_Animation(Player_Animation animID,float animFrame,float animSpeed, bool isLoop,float blendRate) {
	//animation_.changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_PLAYER,(int)animID), isLoop, animSpeed,blendRate, animFrame);
	animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop, blendRate);
}

void Player::addGravity()
{
	gravity_ += 0.02f;
	gravity_ = min(gravity_, 1.5f);//重力最大値
	velocity_ += Vector3::Down*gravity_;

}

void Player::addFloatGravity()
{
	gravity_ += 0.01f;
	gravity_ = min(gravity_, 1.0f);//重力最大値
	velocity_ += -world_->getCamera().lock()->getUpVector().Normalize()*gravity_;
}

void Player::input_to_move(float deltaTime)
{
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f) { return; }

	Vector3 frameVelocity = Vector3::Zero;
	if (!world_->getCamera().expired()) {
		frameVelocity = world_->getCamera().lock()->getMoveForwardPos()*velocity.y*10.0f;//前方向への移動量
		frameVelocity += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
	}
	frameVelocity *= deltaTime;

	velocity_ += frameVelocity;

}

bool Player::isCanDown() const
{
	return (std::find(CantDownState_.begin(), CantDownState_.end(), state_)== CantDownState_.end());//ダウン不可能状態に一致しないか	
}


void Player::to_Idle()
{
	rotation_.Up(Vector3::Up);
	rotation_ = rotation_.NormalizeRotationMatrix_BaseUp();
	if (!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());

	floatPower_ = MaxFloatPower;

}

void Player::update_Idle(float deltaTime)
{
	if (!prevfloor_) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		change_State_and_Anim(Player_State::Jump, Player_Animation::Jump);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}
	if (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R2) &&
		InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::L2)
		) {
		change_State_and_Anim(Player_State::Slide, Player_Animation::Slide);
		return;
	}


	if (prevfloor_)gravity_ = 0.0f;
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f) {
		change_Animation(Player_Animation::Idle);
		Sound::GetInstance().StopSE(SE_ID::RUN_SE);

		return;
	}
	change_Animation(Player_Animation::Run);
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::RUN_SE);

	Vector3 frameVelocity = Vector3::Zero;
	if (!world_->getCamera().expired()) {
		frameVelocity = world_->getCamera().lock()->getMoveForwardPos()*velocity.y*10.0f;//前方向への移動量
		frameVelocity += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
	}
	frameVelocity *= deltaTime;

	velocity_ += frameVelocity;

	rotation_ = rotation_.Forward(frameVelocity.Normalize()).NormalizeRotationMatrix();
}

void Player::end_Idle()
{
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);

}

void Player::to_Move()
{
}

void Player::update_Move(float deltaTime)
{
}

void Player::end_Move()
{
}

void Player::to_Slide()
{
	wind_.initialize();
	world_->getCamera().lock()->inCamera(15.0f);
}

void Player::update_Slide(float deltaTime)
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WIND_SE);

	wind_.update(deltaTime);

	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	addGravity();
	if (prevfloor_)gravity_ = 0.0f;

	Vector2 velocity{ Vector2::Zero };

	int mode = 0;
	mode += (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::R2)) ? 1 : 0;
	mode += (InputChecker::GetInstance().KeyStateDown(InputChecker::Input_Key::L2)) ? 2 : 0;

	Vector3 frameVelocity = Vector3::Zero;

	switch (mode)
	{
	case 0: {
		change_State_and_Anim(Player_State::Idle, Player_Animation::Idle);

		break;
	}
	//片方だけ押されてる場合		
	case 1: {
	}
	case 2: {
		velocityMultPower = 0.9f;
		break;
	}
	//両方押されてる場合
	case 3: {
		frameVelocity += world_->getCamera().lock()->getMoveForwardPos()*25.0f;
		break;
	}
	default:
		break;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		change_State_and_Anim(Player_State::SlideJump, Player_Animation::SlideJump);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}


	frameVelocity *= deltaTime;

	velocity_ += frameVelocity;
	
	if(frameVelocity.Length()>=0.01f)rotation_ = rotation_.Forward(frameVelocity.Normalize()).NormalizeRotationMatrix();
	else if (mode == 1 || mode == 2)rotation_ = rotation_.Forward(world_->getCamera().lock()->getMoveForwardPos()).NormalizeRotationMatrix();
}

void Player::end_Slide()
{
	wind_.stop();
	world_->getCamera().lock()->outCamera();
	Sound::GetInstance().StopSE(SE_ID::WIND_SE);

}

void Player::to_Jump()
{
	velocity_ += rotation_.Up()*10.0f;
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::JUMP_SE);

}

void Player::update_Jump(float deltaTime)
{
	addGravity();
	aerialVelocityKeep();

	//足場についてたら待機に戻る
	if (prevfloor_) {
		change_State_and_Anim(Player_State::Idle, Player_Animation::Idle);
		return;
	}
	//落下が始まったらFallに移行
	if (velocity_.y <= 0.0f) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}

	input_to_move(deltaTime);
}

void Player::end_Jump()
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::LAND_SE);

}

void Player::to_SlideJump()
{
	velocity_ += rotation_.Up()*20.0f;
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::JUMP_SE);

}

void Player::update_SlideJump(float)
{
	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	addGravity();
	aerialVelocityKeep();

	//足場についてたら待機に戻る
	if (prevfloor_) {
		change_State_and_Anim(Player_State::Slide, Player_Animation::Slide);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}

}

void Player::end_SlideJump()
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::LAND_SE);

}

void Player::to_Float()
{
	//velocity_ = Vector3::Zero;

	velocity_ += rotation_.Up()*1.0f;
}

void Player::update_Float(float deltaTime)
{
	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Fly, Player_Animation::Fly);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

}

void Player::end_Float()
{
}

void Player::to_Fly()
{
	if (!world_->getCamera().expired()) {
		flyDirection_ = world_->getCamera().lock()->getCameraForwardPos().Normalize();
		rotation_ = rotation_.Forward(flyDirection_).NormalizeRotationMatrix();
	}
}

void Player::update_Fly(float deltaTime)
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WIND_SE);

	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	//床を歩くかの判定
	Vector3 hitPos;
	Vector3 hitNormal;
	if (world_->getField()->getMesh().collide_line(position_, position_ + flyDirection_*20.0f,(VECTOR*)&hitPos, (VECTOR*)&hitNormal)) {
		rotation_.Up(hitNormal);
		rotation_.NormalizeRotationMatrix_BaseUp();
		if (!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());
		position_ = hitPos + rotation_.Up()*(body_->radius()+body_->length()*0.5f);
		change_State_and_Anim(Player_State::WallRun, Player_Animation::Idle);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}
	
	//入力のチェック
	Vector2 velocity = InputChecker::GetInstance().Stick();
	Vector3 frameVelocity = Vector3::Zero;
	if (velocity.Length() > 0.2f) {
		if (!world_->getCamera().expired()) {
			frameVelocity = world_->getCamera().lock()->getUpVector()*velocity.y*10.0f;//前方向への移動量
			frameVelocity += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
		}
		frameVelocity *= deltaTime;
		velocity_ += frameVelocity;
	}

	float flyPower = (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) ? 1.5f : 1.0f;
	velocity_ += flyDirection_*flyPower;
}

void Player::end_Fly()
{
	Sound::GetInstance().StopSE(SE_ID::WIND_SE);

}

void Player::to_WallRun()
{

}

void Player::update_WallRun(float deltaTime)
{
	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	if (!prevfloor_) {
		change_State_and_Anim(Player_State::FloatFall, Player_Animation::Fall);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		change_State_and_Anim(Player_State::FloatJump, Player_Animation::Jump);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);// playerUpdateFunc_[state_](deltaTime);
		return;
	}

	if (prevfloor_)gravity_ = 0.0f;
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f) {
		change_Animation(Player_Animation::Idle);
		Sound::GetInstance().StopSE(SE_ID::RUN_SE);

		return;
	}
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::RUN_SE);

	change_Animation(Player_Animation::WallRun);
	Vector3 frameVelocity = Vector3::Zero;
	if (!world_->getCamera().expired()) {
		frameVelocity = world_->getCamera().lock()->getMoveForwardPos()*velocity.y*10.0f;//前方向への移動量
		frameVelocity += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
	}
	frameVelocity *= deltaTime;

	velocity_ += frameVelocity;

	//足場へ向きを合わせる
	Vector3 hitPos, hitNormal;
	if (world_->getField()->getMesh().collide_line(position_, position_ + rotation_.Down()*(body_->radius() + body_->length()*0.5f), (VECTOR*)&hitPos, (VECTOR*)&hitNormal)) {
		rotation_.Up(hitNormal);
		rotation_ = rotation_.NormalizeRotationMatrix_BaseUp();
		if (!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());
		position_ = hitPos + rotation_.Up()*(body_->radius() + body_->length()*0.5f);
		//if (change_State_and_Anim(Player_State::WallRun, Player_Animation::WallRun));// playerUpdateFunc_[state_](deltaTime);
		return;
	}

	addFloatGravity();
	rotation_ = rotation_.Forward(frameVelocity.Normalize()).NormalizeRotationMatrix();

}

void Player::end_WallRun()
{
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);

}

void Player::to_FloatJump()
{
	velocity_ += rotation_.Up()*10.0f;
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::JUMP_SE);

}

void Player::update_FloatJump(float deltaTime)
{
	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	addFloatGravity();
	aerialVelocityKeep();

	//足場についてたら待機に戻る
	if (prevfloor_) {
		change_State_and_Anim(Player_State::WallRun, Player_Animation::Idle);
		return;
	}

	
	//落下が始まったらFallに移行
	if (Vector3::Dot(velocity_, world_->getCamera().lock()->getUpVector()) <= 0.0f) {
		change_State_and_Anim(Player_State::FloatFall, Player_Animation::FloatFall);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}

	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f)return;

	Vector3 frameVelocity = Vector3::Zero;
	if (!world_->getCamera().expired()) {
		frameVelocity = world_->getCamera().lock()->getMoveForwardPos()*velocity.y*10.0f;//前方向への移動量
		frameVelocity += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
	}
	frameVelocity *= deltaTime;

	velocity_ += frameVelocity;

}

void Player::end_FloatJump()
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::LAND_SE);

}

void Player::to_FloatFall()
{
}

void Player::update_FloatFall(float deltaTime)
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WIND_SE);

	if (!subFloatPower()) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	if (prevfloor_) {
		change_State_and_Anim(Player_State::WallRun, Player_Animation::Idle);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		change_State_and_Anim(Player_State::Fall, Player_Animation::Fall);
		return;
	}

	addFloatGravity();
	aerialVelocityKeep();

}

void Player::end_FloatFall()
{
	Sound::GetInstance().StopSE(SE_ID::WIND_SE);

}

void Player::to_Fall()
{
	rotation_.Up(Vector3::Up);
	rotation_ = rotation_.NormalizeRotationMatrix_BaseUp();
	if(!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());
}

void Player::update_Fall(float deltaTime)
{
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::WIND_SE);

	if (prevfloor_) {
		change_State_and_Anim(Player_State::Idle, Player_Animation::Idle);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		change_State_and_Anim(Player_State::Float, Player_Animation::Float);
		return;
	}

	addGravity();

	aerialVelocityKeep();

	input_to_move(deltaTime);
}

void Player::end_Fall()
{
	Sound::GetInstance().StopSE(SE_ID::WIND_SE);

}

void Player::to_Blow()
{
	rotation_.Up(Vector3::Up);
	rotation_ = rotation_.NormalizeRotationMatrix_BaseUp();
	if (!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());
	downTimer_.set(10);//10フレームは接地判定をしない

	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::HIT_SE);
}

void Player::update_Blow(float deltaTime)
{
	if (downTimer_()&&prevfloor_) {
		change_State_and_Anim(Player_State::Down, Player_Animation::Down,0.0f,1.0f,false);// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	addGravity();
	velocity_ += blowDirection_;
	blowDirection_ = blowDirection_*0.98f;

}

void Player::end_Blow()
{
}

void Player::to_Down()
{
	downTimer_.set(120);//120フレーム数える
}

void Player::update_Down(float deltaTime)
{
	//ダウン時間が終わったら次へ
	if (downTimer_()) {
		change_State_and_Anim(Player_State::GetUp, Player_Animation::GetUp,0.0f,1.0f,false);// playerUpdateFunc_[state_](deltaTime);
		return;

	}
}

void Player::end_Down()
{
}

void Player::to_GetUp()
{
}

void Player::update_GetUp(float deltaTime)
{
	if (animation_.IsAnimEnd()) {
		change_State_and_Anim(Player_State::Idle, Player_Animation::Idle);// playerUpdateFunc_[state_](deltaTime);
		return;
	}

}

void Player::end_GetUp()
{
}

void Player::to_OutOfField()
{
	
	world_->getFade().addCallBack([&] {
		position_ = Vector3{ 0,10.0f,0 };
		change_State_and_Anim(Player_State::Idle, Player_Animation::Idle); 
	});
	world_->getFade().start();
}

void Player::update_OutOfField(float deltaTime)
{
	if (world_->getFade().isActive())return;

}

void Player::end_OutOfField()
{
}

bool Player::subFloatPower(float rate)
{
	floatPower_ -= 0.1f*rate;
	floatPower_ = MathHelper::Clamp(floatPower_, 0.0f, MaxFloatPower);
	return floatPower_ > 0.0f;
}
