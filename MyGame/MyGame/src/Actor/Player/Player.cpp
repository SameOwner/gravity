#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../Other/CameraActor.h"

Player::Player(IWorld* world, const Vector3& position, const IBodyPtr& body):
	Actor(world,"Player",position,body)
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));
	//animation_.ChangeAnim()
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {update_Idle(deltaTime); };
	playerToNextModeFunc_[Player_State::Idle]= [this]() {to_Idle(); };
	playerEndModeFunc_[Player_State::Idle]= [this]() {end_Idle(); };
	
	playerUpdateFunc_[Player_State::Float] = [this](float deltaTime) {update_Float(deltaTime); };
	playerToNextModeFunc_[Player_State::Float] = [this]() {to_Float(); };
	playerEndModeFunc_[Player_State::Float] = [this]() {end_Float(); };

	playerUpdateFunc_[Player_State::Fly] = [this](float deltaTime) {update_Fly(deltaTime); };
	playerToNextModeFunc_[Player_State::Fly] = [this]() {to_Fly(); };
	playerEndModeFunc_[Player_State::Fly] = [this]() {end_Fly(); };

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
		position_ = result+body_->points(0)+Vector3::Up*body_->radius();
	}
	else prevfloor_ = false;
}

void Player::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f);
	//前後を合わせる
	animation_.Draw(Matrix(rotation_)*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(drawPosition));
	body_->transform(getPose())->draw();
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

void Player::to_Idle()
{
}

void Player::update_Idle(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::R1)) {
		if (change_State_and_Anim(Player_State::Float, Player_Animation::Float));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	if (prevfloor_)gravity_ = 0.0f;
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f)return;
	Vector3 frameVelocty = world_->getCamera().lock()->getMoveForwardPos()*velocity.y;//前方向への移動量
	frameVelocty += world_->getCamera().lock()->getMoveRightPos()*velocity.x;
	frameVelocty *= deltaTime;
	velocity_ += Vector3(frameVelocty.x, 0.0f, frameVelocty.z);

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
	flyDirection_ = world_->getCamera().lock()->getMoveForwardPos().Normalize();
}

void Player::update_Fly(float deltaTime)
{
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

void Player::to_Fall()
{
}

void Player::update_Fall(float deltaTime)
{
	if (prevfloor_) {
		if (change_State_and_Anim(Player_State::Idle, Player_Animation::Idle));// playerUpdateFunc_[state_](deltaTime);
		return;
	}
	gravity_ += 0.1f;

	velocity_ += Vector3::Down*gravity_;
}

void Player::end_Fall()
{
}
