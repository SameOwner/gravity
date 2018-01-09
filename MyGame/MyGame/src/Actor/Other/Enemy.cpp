#include "Enemy.h"

Enemy::Enemy(IWorld * world, const Vector3 & position, const IBodyPtr & body) :
	Actor(world, "Enemy", position, body)
{
}

void Enemy::initialize()
{
	target_.reset();
}

void Enemy::setTarget_Player()
{
	target_ = world_->findActor("Player");
}

void Enemy::update(float deltaTime)
{

	if (target_.expired())return;

	if (Vector3::Distance(position_, target_.lock()->getPosition()) <= 100.0f) {
		
	}
}

void Enemy::draw() const
{
}
