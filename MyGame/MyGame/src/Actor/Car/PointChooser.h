#pragma once
#include"../../Math/Vector3.h"

class IWorld;
class PointChooser {
public:
	PointChooser(IWorld* world);
	//���݃|�C���g��ݒ�
	void setPoint(const Vector3& position);
	//���̃S�[���n�_������(�����_��)
	void chooseGoal();
	//���̃S�[���n�_������(�t������)
	void chooseGoal_Forward(int prevPoint);

	Vector3 operator ()(bool& isEnd);
private:
	IWorld* world_;
	int currentPoint_;
	int goal_;
};