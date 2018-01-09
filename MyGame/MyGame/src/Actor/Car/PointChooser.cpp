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
	int goal = Random::GetInstance().Range(0, world_->getCityMap().getSize() - 2);//2���炷���Ŏ��g��͈͂��珜��
	if (goal < goal_)goal_ = goal;//���g��菬�����l�͂��̂܂�
	else goal_ = goal + 1;//���g�ȏ�ł����+1���鎖�Ŏ��g����
}

void PointChooser::chooseGoal_Forward(int prevPoint)
{
	std::vector<int> forwardPoints;//�t�����Ȃ����[�g
	int checki;
	for (int i = 0; i < world_->getCityMap().getSize(); i++) {
		checki=world_->getCityMap().getNextCarPoint(currentPoint_, i);
		if (checki != -1 &&//��O����������
			checki != prevPoint&&//�O�ʉ߂����|�C���g�ł��Ȃ�
			checki != currentPoint_) {//������|�C���g�ł��Ȃ��ꍇ
			forwardPoints.push_back(i);//���[�g�Ƃ��ĔF��
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
