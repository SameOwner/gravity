#include "Enemy.h"
#include"../../Graphic/Model.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Define.h"
#include"../../Field/CityMap.h"
#include"EnemyBullet.h"

static const Vector3 upVector{ 0.0f,35.0f,0.0f };
static const float defCoolTime = 8.0f;
Enemy::Enemy(IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "Enemy", position + upVector, body), animation_(), chooser_(world), timer_{}, coolTime_{}
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ENEMY));
	bool isEnd;
	nextPoint_ = chooser_(isEnd, ChooseType::CanBack);
	nextPoint_.y = world_->getCityMap().getFlyPointY(chooser_.getCurrentPoint());

	coolTime_.setTime(defCoolTime);
}

void Enemy::initialize()
{
	target_.reset();
	setTarget_Player();
	changeState(State::Idle);
}

void Enemy::setTarget_Player()
{
	target_ = world_->findActor("Player");
}

void Enemy::update(float deltaTime)
{
	animation_.Update(1.0f);
	coolTime_();

	switch (state_)
	{
	case Enemy::State::Idle:idle(deltaTime);
		break;
	case Enemy::State::Move:move(deltaTime);
		break;
	case Enemy::State::Aim:aim(deltaTime);
		break;
	case Enemy::State::Attack:attack(deltaTime);
		break;
	default:
		break;
	}
	//�Ԃ�������
	Vector3 result;
	//�ǂƂԂ��Ă���
	//if (field(result))position_ = result;

}

void Enemy::draw() const
{
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);

	animation_.Draw(pose);
	body_->transform(pose)->draw();

	//DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "%f:%f:%f", position_.x, position_.y, position_.z);

}

void Enemy::onCollide(Actor & other)
{
	//�v���C���[�ƐڐG�����玀��
	if (other.getGroup() == ActorGroup::PLAYER_ACTOR) {
		isDead_ = true;
	}

}

bool Enemy::checkAttack()
{
	if (Vector3::Distance(position_, target_.lock()->getPosition()) <= 100.0f) {
		if (coolTime_.isTime()) {
			changeState(State::Aim , false);
			return true;
		}
	}
	return false;
}

void Enemy::idle(float deltaTime)
{
	if (target_.expired())return;

	if (checkAttack())return;

	if (timer_()) {
		changeState(State::Move);
	}
}

void Enemy::move(float deltaTime)
{
	if (checkAttack())return;

	Vector3 toNextPoint = (nextPoint_ - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toNextPoint);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	rotation_ *= Matrix::CreateFromAxisAngle(Vector3::Up, checkIsLeftDot*5.0f);

	float checkIsUpDot = Vector3::Dot(Vector3::Up, toNextPoint);//���ςŏ㉺����
	//rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Left(), checkIsLeftDot*5.0f);
	position_ += rotation_.Forward()*0.7f;
	position_.y += checkIsUpDot;

	bool isEnd = false;
	if (Vector2::Distance(Vector2(position_.x, position_.z), Vector2(nextPoint_.x, nextPoint_.z)) <= 50.0f) {
		nextPoint_ = chooser_(isEnd, ChooseType::CanBack) + upVector;
		nextPoint_.y = world_->getCityMap().getFlyPointY(chooser_.getCurrentPoint());
	}
	if (isEnd) {//�ړI�n�ɓ��B������ҋ@��Ԃ�
		changeState(State::Idle);
		return;
	}
}

void Enemy::aim(float deltaTime)
{
	Vector3 toPlayer = (target_.lock()->getPosition() - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toPlayer);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*5.0f);

	if (checkIsLeftDot <= 0.1f) {
		changeState(State::Attack, false);
	}
}

void Enemy::attack(float deltaTime)
{
	Vector3 toPlayer = (target_.lock()->getPosition() - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toPlayer);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*5.0f);



	if (animation_.IsAnimEnd()) {
		changeState(State::Move);
	}
}

void Enemy::changeState(State state, bool isLoop)
{
	//�I��������
	switch (state)
	{
	case Enemy::State::Idle:
		break;
	case Enemy::State::Move:
		break;
	case Enemy::State::Attack:
		coolTime_.setTime(defCoolTime);
		break;
	default:
		break;
	}
	state_ = state;
	animation_.ChangeAnim(animHandleConv.at(state),0.0f,1.0f,isLoop);

	//�J�n������
	switch (state)
	{
	case Enemy::State::Idle:
		timer_.set(180);
		break;
	case Enemy::State::Move:
		chooser_.setPoint(position_);
		bool isEnd;
		nextPoint_ = chooser_(isEnd,ChooseType::CanBack) + upVector;
		nextPoint_.y = world_->getCityMap().getFlyPointY(chooser_.getCurrentPoint());
		break;
	case Enemy::State::Attack:
		world_->addActor(ActorGroup::ENEMY_ACTOR, std::make_shared<EnemyBullet>(world_,position_ + rotation_.Forward(), target_.lock()->getPosition() - position_));
		break;
	default:
		break;
	}
}
