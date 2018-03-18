#pragma once
#include"../../Math/Vector3.h"

class IWorld;

enum class ChooseType {
	NotBack,//逆走不可能
	CanBack//逆走可能
};

class PointChooser {
public:
	PointChooser(IWorld* world);
	//現在ポイントを設定
	void setPoint(const Vector3& position);
	//次のゴール地点を決定(ランダム)
	void chooseGoal();
	//次のゴール地点を決定(逆走無し)
	void chooseGoal_Forward(int prevPoint);

	int getCurrentPoint()const;

	Vector3 operator ()(bool& isEnd, ChooseType type=ChooseType::NotBack);
private:
	IWorld* world_;
	int currentPoint_;
	int goal_;
};