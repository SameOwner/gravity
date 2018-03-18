#pragma once
#include"../../Math/Vector3.h"
#include<vector>
class IWorld;

class CityWalkPointChooser {
public:
	CityWalkPointChooser(IWorld* world, const Vector3& position, int walkSheetType);
	//現在ポイントを設定
	void setPoint(const Vector3& position);
	//次のゴール地点を決定(ランダム)
	void chooseGoal();
	int getNextPoint()const;

	Vector3 operator ()(const Vector3& position, bool& isEnd);//検索
private:
	int walkSheetType_;//巡回する対象シート
	IWorld* world_;
	int currentPoint_;//今回の経路の開始地点
	int goal_;//目的地点
	std::vector<int> path_;//移動ルート
};