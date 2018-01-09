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
	int goal = Random::GetInstance().Range(0, world_->getCityMap().getSize() - 2);//2個ずらす事で自身を範囲から除く
	if (goal < goal_)goal_ = goal;//自身より小さい値はそのまま
	else goal_ = goal + 1;//自身以上であれば+1する事で自身除く
}

void PointChooser::chooseGoal_Forward(int prevPoint)
{
	std::vector<int> forwardPoints;//逆走しないルート
	int checki;
	for (int i = 0; i < world_->getCityMap().getSize(); i++) {
		checki=world_->getCityMap().getNextCarPoint(currentPoint_, i);
		if (checki != -1 &&//例外が発生せず
			checki != prevPoint&&//前通過したポイントでもなく
			checki != currentPoint_) {//今いるポイントでもない場合
			forwardPoints.push_back(i);//ルートとして認識
		}
	}
	int goal = Random::GetInstance().Randomize(forwardPoints);
	goal_ = goal;

}

Vector3 PointChooser::operator()(bool& isEnd)
{
	int prevPoint = currentPoint_;
	currentPoint_ = world_->getCityMap().getNextCarPoint(currentPoint_, goal_);
	isEnd = (currentPoint_ == goal_||currentPoint_==-1);
	if (isEnd) {
		chooseGoal_Forward(prevPoint);
	}
	return world_->getCityMap().getPosition(currentPoint_);
}
