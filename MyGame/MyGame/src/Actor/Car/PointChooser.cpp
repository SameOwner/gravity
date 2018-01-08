#include "PointChooser.h"
#include"../../World/IWorld.h"
#include"../../Field/CityMap.h"
#include"../../Math/Random.h"

PointChooser::PointChooser(IWorld * world):
	world_(world), currentPoint_(0),goal_(0)
{
	chooseGoal();
}

void PointChooser::setPoint(const Vector3 & position)
{
	currentPoint_ = world_->getCityMap().getNearestPoint(position);
}

void PointChooser::chooseGoal()
{
	int goal = Random::GetInstance().Range(0, world_->getCityMap().getSize() - 2);
	if (goal < goal_)goal_ = goal;
	else goal_ = goal + 1;
}

Vector3 PointChooser::operator()(bool& isEnd)
{
	currentPoint_ = world_->getCityMap().getNextCarPoint(currentPoint_, goal_);
	isEnd = (currentPoint_ == goal_||currentPoint_==-1);
	if (isEnd) {
		chooseGoal();
	}
	return world_->getCityMap().getPosition(currentPoint_);
}
