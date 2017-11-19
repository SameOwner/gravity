#include "CameraActor.h"

CameraActor::CameraActor(IWorld * world, IBodyPtr body) :
	Actor(world, "Camera", Vector3::Zero, body),target_()
{
}

void CameraActor::initialize()
{
	isActive_ = true;
	target_.reset();
}

void CameraActor::update(float deltaTime)
{
}

void CameraActor::draw() const
{
}

void CameraActor::end()
{
}

void CameraActor::setTarget(std::shared_ptr<Actor>& target)
{
	target_ = target;
}
