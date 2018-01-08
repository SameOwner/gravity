#include "Car.h"
#include"../../Graphic/Model.h"


#include"../../Input/InputChecker.h"
#include"../Other/CameraActor.h"

Car::Car(IWorld * world, const Vector3 & position, MODEL_ID id, const IBodyPtr & body):
	Actor(world,"Car",position,body),modelid_(id), chooser_(world), nextPoint_(position){
	chooser_.setPoint(position_);
	bool isEnd;
	nextPoint_ = chooser_(isEnd);

}


void Car::update(float deltaTime)
{
	Vector3 toNextPoint = (nextPoint_ - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toNextPoint);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	//float angle = 0.0f;//���������S�ɂ����Ă����]�͖���
	//if (checkIsLeftDot > 0.0f)angle = -1.f;//������
	//else if (checkIsLeftDot < 0.0f)angle = 1.f;//�E����
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*5.0f);
	position_ += rotation_.Forward()*3.0f;
	bool isEnd;
	if (Vector2::Distance(Vector2(position_.x,position_.z), Vector2(nextPoint_.x,nextPoint_.z)) <= 10.0f) {
		nextPoint_ = chooser_(isEnd);
	}
}

void Car::draw() const
{
	Model::GetInstance().Draw(modelid_, Matrix(rotation_).Translation(position_));
	body_->transform(getPose())->draw();
}

void Car::onCollide(Actor & other)
{
}
