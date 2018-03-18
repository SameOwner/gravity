#pragma once
#include"../../Math/Vector3.h"
#include<vector>
class IWorld;

class CityWalkPointChooser {
public:
	CityWalkPointChooser(IWorld* world, const Vector3& position, int walkSheetType);
	//���݃|�C���g��ݒ�
	void setPoint(const Vector3& position);
	//���̃S�[���n�_������(�����_��)
	void chooseGoal();
	int getNextPoint()const;

	Vector3 operator ()(const Vector3& position, bool& isEnd);//����
private:
	int walkSheetType_;//���񂷂�ΏۃV�[�g
	IWorld* world_;
	int currentPoint_;//����̌o�H�̊J�n�n�_
	int goal_;//�ړI�n�_
	std::vector<int> path_;//�ړ����[�g
};