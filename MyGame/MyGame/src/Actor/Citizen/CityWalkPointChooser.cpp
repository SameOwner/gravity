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
	//���݈ʒu�̐ݒ�ƁA�ړI�n�̃��Z�b�g
	currentPoint_ = world_->getWalkMap().getNearestNode(walkSheetType_, position);
	goal_ = currentPoint_;
}

void CityWalkPointChooser::chooseGoal()
{
	currentPoint_ = goal_;//�O�̃S�[���n�_���J�n�n�_�ɂ���
	int goal = Random::GetInstance().Range(0, world_->getWalkMap().node_count(walkSheetType_) - 2);//2���炷���Ŏ��g��͈͂��珜��
	if (goal < goal_)goal_ = goal;//���g��菬�����l�͂��̂܂�
	else goal_ = goal + 1;//���g�ȏ�ł����+1���鎖�Ŏ��g����

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
	Vector3 next = world_->getWalkMap().getNode(walkSheetType_, getNextPoint()).position;//���̖ړI�n������Ă���
	next.y = position.y;//y���͖���
	if (Vector3::Distance(position, next) <= 10.0f) {//�ړI�n�ɓ��B������
		if (path_.front() == goal_) {//�ŏI�ړI�n�ɓ��B������
			isEnd = true;//�I����������
			return position;//�ړ����Ȃ�
		}
		path_.erase(path_.begin());//���̖ړI�n�ֈړ�
	}
	return world_->getWalkMap().getNode(walkSheetType_, getNextPoint()).position;//���̖ړI�n��n��
}
