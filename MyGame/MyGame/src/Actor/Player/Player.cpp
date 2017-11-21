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

}

void Player::initialize()
{
	state_ = Player_State::Idle;


}

void Player::update(float deltaTime)
{
	playerUpdateFunc_[state_](deltaTime);

	animation_.Update(deltaTime);

	position_ += velocity_;
	velocity_ *= 0.8f;
}

void Player::draw() const
{
	//�`��ʒu�����킹��(�Ō��Vector3�̓��f�����g�̃Y��)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f);
	//�O������킹��
	animation_.Draw(Matrix(rotation_)*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(drawPosition));
	body_->transform(getPose())->draw();
}

bool Player::change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame, float animSpeed, bool isLoop)
{
	//������Ԃɂ͑J�ڂ��Ȃ�
	if (state_ == state)return false;
	//��ɃA�j���[�V������؂�ւ�
	change_Animation(animID, animFrame, animSpeed, isLoop);

	if (!change_State(state))return false;

	return true;
}

bool Player::change_State(Player_State state)
{
	//��Ԃ��ς��Ȃ��Ȃ玸�s
	if (state_ == state)return false;

	//��Ԃ̏I���������s��
	playerEndModeFunc_[state_]();
	//��Ԃ��X�V
	state_ = state;
	//��ԕύX���s��
	playerToNextModeFunc_[state_]();
	//�X�V����
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
		if (change_State_and_Anim(Player_State::Float, Player_Animation::Float))playerUpdateFunc_[state_](deltaTime);
	}
	Vector2 velocity = InputChecker::GetInstance().Stick();
	if (velocity.Length() <= 0.2f)return;
	Vector3 frameVelocty = world_->getCamera().lock()->getMoveForwardPos()*velocity.y;//�O�����ւ̈ړ���
	frameVelocty += world_->getCamera().lock()->getMoveRightPos()*velocity.x;
	frameVelocty *= deltaTime;
	velocity_ += Vector3(frameVelocty.x, 0.0f, frameVelocty.z);

	rotation_ = rotation_.Forward(velocity_.Normalize()).NormalizeRotationMatrix();

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
}

void Player::update_Float(float deltaTime)
{
}

void Player::end_Float()
{
}
