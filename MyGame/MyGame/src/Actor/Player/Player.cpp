#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"

Player::Player(IWorld* world, const Vector3& position, const IBodyPtr& body):
	Actor(world,"Player",position,body)
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));
	//animation_.ChangeAnim()
	playerUpdateFunc_[Player_State::Idle] = [this](float deltaTime) {update_Idle(deltaTime); };
	playerToNextModeFunc_[Player_State::Idle]= [this]() {to_Idle(); };
	playerEndModeFunc_[Player_State::Idle]= [this]() {end_Idle(); };
	
}

void Player::initialize()
{
}

void Player::update(float deltaTime)
{
	animation_.Update(deltaTime);
}

void Player::draw() const
{
	animation_.Draw(Matrix(rotation_).Translation(position_));
	body_->draw();
}

bool Player::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop)
{
	if (state_ == state)return false;
	
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
	if (InputChecker::GetInstance().Stick().Length() >= 0.2f) {
		
	}
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
