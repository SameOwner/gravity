#pragma once
#include"../../Math/Vector3.h"

class IWorld;

enum class ChooseType {
	NotBack,//�t���s�\
	CanBack//�t���\
};

class PointChooser {
public:
	PointChooser(IWorld* world);
	//���݃|�C���g��ݒ�
	void setPoint(const Vector3& position);
	//���̃S�[���n�_������(�����_��)
	void chooseGoal();
	//���̃S�[���n�_������(�t������)
	void chooseGoal_Forward(int prevPoint);

	int getCurrentPoint()const;

	Vector3 operator ()(bool& isEnd, ChooseType type=ChooseType::NotBack);
private:
	IWorld* world_;
	int currentPoint_;
	int goal_;
};