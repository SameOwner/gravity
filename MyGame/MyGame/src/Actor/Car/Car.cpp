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
	Vector3 toNextPoint = (nextPoint_ - position_).Normalize();//自身から次の地点へのベクトル
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toNextPoint);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	//float angle = 0.0f;//もしも完全にあってたら回転は無し
	//if (checkIsLeftDot > 0.0f)angle = -1.f;//左向き
	//else if (checkIsLeftDot < 0.0f)angle = 1.f;//右向き
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
