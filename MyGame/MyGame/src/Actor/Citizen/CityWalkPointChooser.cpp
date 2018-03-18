#include "CityWalkPointChooser.h"
#include"../../World/IWorld.h"
#include"../../Field/WalkMap.h"
#include"../../Math/Random.h"
#include"../../Field/WalkPath.h"
#include<assert.h>

CityWalkPointChooser::CityWalkPointChooser(IWorld * world,const Vector3& position,int walkSheetType):world_(world),walkSheetType_(walkSheetType)
{
	setPoint(position);
}

void CityWalkPointChooser::setPoint(const Vector3& position)
{
	//現在位置の設定と、目的地のリセット
	currentPoint_ = world_->getWalkMap().getNearestNode(walkSheetType_, position);
	goal_ = currentPoint_;
}

void CityWalkPointChooser::chooseGoal()
{
	currentPoint_ = goal_;//前のゴール地点を開始地点にする
	int goal = Random::GetInstance().Range(0, world_->getWalkMap().node_count(walkSheetType_) - 2);//2個ずらす事で自身を範囲から除く
	if (goal < goal_)goal_ = goal;//自身より小さい値はそのまま
	else goal_ = goal + 1;//自身以上であれば+1する事で自身除く

	auto path = WalkPath::find_path(world_->getWalkMap(), walkSheetType_, currentPoint_, goal_);
	path_.clear();
	path_.assign(path.rbegin(), path.rend());
}

int CityWalkPointChooser::getNextPoint() const
{
	assert(!path_.empty());
	return path_.front();
}

Vector3 CityWalkPointChooser::operator()(const Vector3& position, bool& isEnd)
{
	isEnd = false;
	Vector3 next = world_->getWalkMap().getNode(walkSheetType_, getNextPoint()).position;//次の目的地を取ってくる
	next.y = position.y;//y軸は無視
	if (Vector3::Distance(position, next) <= 10.0f) {//目的地に到達したら
		if (path_.front() == goal_) {//最終目的地に到達したら
			isEnd = true;//終了を教えて
			return position;//移動しない
		}
		path_.erase(path_.begin());//次の目的地へ移動
	}
	return world_->getWalkMap().getNode(walkSheetType_, getNextPoint()).position;//次の目的地を渡す
}
