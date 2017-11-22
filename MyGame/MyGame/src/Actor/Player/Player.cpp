#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../Other/CameraActor.h"
#include"../../Field/FieldBase.h"

Player::Player(IWorld* world, const Vector3& position, const IBodyPtr& body):
	Actor(world,"Player",position,body)
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));
	//animation_.ChangeAnim()
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {update_Idle(deltaTime); };
	playerToNextModeFunc_[Player_State::Idle]= [this]() {to_Idle(); };
	playerEndModeFunc_[Player_State::Idle]= [this]() {end_Idle(); };
	
	playerUpdateFunc_[Player_State::Jump] = [this](float deltaTime) {update_Jump(deltaTime); };
	playerToNextModeFunc_[Player_State::Jump] = [this]() {to_Jump(); };
	playerEndModeFunc_[Player_State::Jump] = [this]() {end_Jump(); };

	playerUpdateFunc_[Player_State::Float] = [this](float deltaTime) {update_Float(deltaTime); };
	playerToNextModeFunc_[Player_State::Float] = [this]() {to_Float(); };
	playerEndModeFunc_[Player_State::Float] = [this]() {end_Float(); };

	playerUpdateFunc_[Player_State::Fly] = [this](float deltaTime) {update_Fly(deltaTime); };
	playerToNextModeFunc_[Player_State::Fly] = [this]() {to_Fly(); };
	playerEndModeFunc_[Player_State::Fly] = [this]() {end_Fly(); };

	playerUpdateFunc_[Player_State::WallRun] = [this](float deltaTime) {update_WallRun(deltaTime); };
	playerToNextModeFunc_[Player_State::WallRun] = [this]() {to_WallRun(); };
	playerEndModeFunc_[Player_State::WallRun] = [this]() {end_WallRun(); };

	playerUpdateFunc_[Player_State::Fall] = [this](float deltaTime) {update_Fall(deltaTime); };
	playerToNextModeFunc_[Player_State::Fall] = [this]() {to_Fall(); };
	playerEndModeFunc_[Player_State::Fall] = [this]() {end_Fall(); };

}

void Player::initialize()
{
	state_ = Player_State::Idle;
	gravity_ = 0.0f;
	prevfloor_ = false;
}

void Player::update(float deltaTime)
{
	playerUpdateFunc_[state_](deltaTime);

	animation_.Update(deltaTime);

	position_ += velocity_;
	velocity_ *= 0.8f;

	Vector3 result;
	if (field(result))position_ = result;
	if (floor(result)) {
		prevfloor_ = true;
		position_ = result+rotation_.Up()*(body_->length()*0.5f+body_->radius());
	}
	else prevfloor_ = false;
}

void Player::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f);
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
	body_->transform(getPose())->draw();
}

void Player::aerialVelocityKeep()
{
	velocity_.x *= 2.3f - MathHelper::Clamp(std::abs(velocity_.x), 1.0f, 1.05f);
	velocity_.z *= 2.3f - MathHelper::Clamp(std::abs(velocity_.z), 1.0f, 1.05f);

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

void Player::change_Animation(Player_Animation animID, float animFrame, float animSpeed, bool isLoop) {
	animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop);
}

void Player::addGravity()
{
	gravity_ += 0.05f;
	velocity_ += Vector3::Down*gravity_;

}


void Player::to_Idle()
{
}

void Player::update_Idle(float deltaTime)
{
	if (!prevfloor_) {
		if (change_State_and_Anim(Player_State::Fall, Player_Animation::Fall));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
		if (change_State_and_Anim(Player_State::Jump, Player_Animation::Jump));// playerUpdateFunc_[state_](deltaTime);
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Float, Player_Animation::Float));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (prevfloor_)gravity_ = 0.0f;
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f)return;

	Vector3 frameVelocty = Vector3::Zero;
	if (!world_->getCamera().expired()) {
		frameVelocty = world_->getCamera().lock()->getMoveForwardPos()*velocity.y*10.0f;//前方向への移動量
		frameVelocty += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
	}
	frameVelocty *= deltaTime;

	velocity_ += frameVelocty;//Vector3(frameVelocty.x, 0.0f, frameVelocty.z);

	rotation_ = rotation_.Forward(frameVelocty.Normalize()).NormalizeRotationMatrix();
}

void Player::end_Idle()
{
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

void Player::to_Jump()
{
	velocity_ += rotation_.Up()*10.0f;
}

void Player::update_Jump(float deltaTime)
{
	addGravity();
	aerialVelocityKeep();

	//足場についてたら待機に戻る
	if (prevfloor_) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	//落下が始まったらFallに移行
	if (velocity_.y <= 0.0f) {
		if (change_State_and_Anim(Player_State::Fall, Player_Animation::Fall));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Float, Player_Animation::Float));// playerUpdateFunc_[state_](deltaTime);
		return;
	}


}

void Player::end_Jump()
{
}

void Player::to_Float()
{
	//velocity_ = Vector3::Zero;

	velocity_ += rotation_.Up()*1.0f;
}

void Player::update_Float(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Fly, Player_Animation::Fly));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		if (change_State_and_Anim(Player_State::Fall, Player_Animation::Fall));// playerUpdateFunc_[state_](deltaTime);
		return;
	}

}

void Player::end_Float()
{
}

void Player::to_Fly()
{
	if (!world_->getCamera().expired())flyDirection_ = world_->getCamera().lock()->getCameraForwardPos().Normalize();
}

void Player::update_Fly(float deltaTime)
{
	Vector3 hitPos;
	Vector3 hitNormal;
	if (world_->getField()->getMesh().collide_line(position_, position_ + flyDirection_*10.0f,(VECTOR*)&hitPos, (VECTOR*)&hitNormal)) {
		rotation_.Up(hitNormal);
		rotation_.NormalizeRotationMatrix();
		if (!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());
		position_ = hitPos + rotation_.Up()*(body_->radius()+body_->length()*0.5f);
		if (change_State_and_Anim(Player_State::WallRun, Player_Animation::WallRun));// playerUpdateFunc_[state_](deltaTime);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Float, Player_Animation::Float));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::L1)) {
		if (change_State_and_Anim(Player_State::Fall, Player_Animation::Fall));// playerUpdateFunc_[state_](deltaTime);
		return;
	}

	velocity_ += flyDirection_*1.0f;
}

void Player::end_Fly()
{
}

void Player::to_WallRun()
{
}

void Player::update_WallRun(float deltaTime)
{
	//if (!prevfloor_) {
	//	if (change_State_and_Anim(Player_State::Fall, Player_Animation::Fall));// playerUpdateFunc_[state_](deltaTime);
	//	return;
	//}
	//if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B)) {
	//	if (change_State_and_Anim(Player_State::Jump, Player_Animation::Jump));// playerUpdateFunc_[state_](deltaTime);
	//}
	//if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
	//	if (change_State_and_Anim(Player_State::Float, Player_Animation::Float));// playerUpdateFunc_[state_](deltaTime);
	//	return;
	//}
	if (prevfloor_)gravity_ = 0.0f;
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f)return;

	Vector3 frameVelocty = Vector3::Zero;
	if (!world_->getCamera().expired()) {
		frameVelocty = world_->getCamera().lock()->getMoveForwardPos()*velocity.y*10.0f;//前方向への移動量
		frameVelocty += world_->getCamera().lock()->getMoveRightPos()*velocity.x*10.0f;
	}
	frameVelocty *= deltaTime;

	velocity_ += frameVelocty;

	//rotation_ = rotation_.Forward(frameVelocty.Normalize()).NormalizeRotationMatrix();

}

void Player::end_WallRun()
{
}

void Player::to_Fall()
{
	rotation_.Up(Vector3::Up);
	rotation_ = rotation_.NormalizeRotationMatrix();
	if(!world_->getCamera().expired())world_->getCamera().lock()->setUpVector(rotation_.Up());
}

void Player::update_Fall(float deltaTime)
{
	if (prevfloor_) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Float, Player_Animation::Float));// playerUpdateFunc_[state_](deltaTime);
		return;
	}

	addGravity();

	aerialVelocityKeep();
}

void Player::end_Fall()
{
}
