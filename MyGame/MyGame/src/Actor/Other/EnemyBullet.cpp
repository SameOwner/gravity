#include "EnemyBullet.h"
#include"../Body/BoundingSphere.h"
#include"../../ID/EnumIDs.h"
#include"../../Field/FieldBase.h"

static const float movePower = 1.0f;
EnemyBullet::EnemyBullet(IWorld* world,const Vector3 & position, const Vector3 & velocity):
	Actor(world,"EnemyBullet",position,std::make_shared<BoundingSphere>(Vector3::Zero,3.0f)),
	velocity_{velocity}, timer_()
{
	timer_.setTime(5.0f);
	timer_.setFunc([&] {isDead_ = true; });
}

void EnemyBullet::update(float deltaTime)
{
	timer_();
	position_ += velocity_.Normalize()*movePower;
	//if (world_->getField()->getMesh().collide_sphere(position_, 3.0f)) {
	//	isDead_ = true;
	//}
}

void EnemyBullet::draw() const
{
	//body_->transform(getPose())->draw();
	DrawSphere3D(position_, body_->radius(), 32, GetColor(255, 0, 0), GetColor(125, 125, 125), TRUE);

}

void EnemyBullet::onCollide(Actor & other)
{
	if (other.getName() == "Player") {
		Vector3 hitdir = (other.getPosition() - position_);

		other.receiveMessage(EventMessage::Hit_Bullet, (void*)&hitdir);

		isDead_ = true;
	}
}
