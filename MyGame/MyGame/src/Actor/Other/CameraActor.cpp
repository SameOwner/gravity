#include "CameraActor.h"
#include"../../Input/InputChecker.h"

//�J�����𗣂�����
const float defaultCameraDistance = 30.0f;
CameraActor::CameraActor(IWorld * world,const Vector3& position, IBodyPtr body) :
	Actor(world, "Camera", position, body),target_()
{
}

void CameraActor::initialize()
{
	isActive_ = true;
	cameraDistance_ = defaultCameraDistance;
	rotate_ = Vector2::Zero;//�J�����̉�]
	movefwPos_ = Vector3::Zero;
	moverhPos_ = Vector3::Zero;
	camerafwPos_ = Vector3::Zero;
	upVector_ = Vector3::Up;
	target_.reset();
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
}

void CameraActor::update(float deltaTime)
{
	Vector3 movePos = Vector3::Zero;//���t���[���p�̃J�����ړ��x�N�g��
	Vector2 move = InputChecker::GetInstance().RightStick()*3.f;
	if (move.Length() > 0.2f) {
		rotate_ += move;
		//�J�����̉�]���E��ݒ肷��
		rotate_.y = MathHelper::Clamp(rotate_.y, -80.0f, 80.0f);
	}

	movePos.x = -cameraDistance_*MathHelper::Sin(rotate_.x) * MathHelper::Cos(rotate_.y);
	movePos.y = -cameraDistance_*MathHelper::Sin(rotate_.y);
	movePos.z = -cameraDistance_*MathHelper::Cos(rotate_.x) * MathHelper::Cos(rotate_.y);


	movePos = movePos*Matrix(Matrix::Identity).Up(upVector_).NormalizeRotationMatrix();
	/*
	movePos.x = cameraDistance_*MathHelper::Sin(rotate_.y) * MathHelper::Cos(rotate_.x);
	movePos.y = -cameraDistance_*MathHelper::Cos(rotate_.y);
	movePos.z = -cameraDistance_*MathHelper::Sin(rotate_.y) * MathHelper::Sin(rotate_.x);
	rotate.X = Math.Cos(x) * Math.Cos(y);
	rotate.Y = Math.Sin(y);
	rotate.Z = Math.Sin(x) * Math.Cos(y);
	*/

	//// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���̓J�����̎�����������x�����𔲂�������
	//UpMoveVec = VSub(cam.Target, cam.Eye);
	//UpMoveVec.y = 0.0f;

	//// �����{�^���u���v���������Ƃ��̃v���C���[�̈ړ��x�N�g���͏���������Ƃ��̕����x�N�g���Ƃx���̃v���X�����̃x�N�g���ɐ����ȕ���
	//LeftMoveVec = VCross(UpMoveVec, VGet(0.0f, 1.0f, 0.0f));

	camerafwPos_ = (-movePos).Normalize();
	Vector3 mp = movePos;
	mp.Normalize();
	float angle = MathHelper::ACos(Vector3::Dot(Vector3::Up, mp));
	Vector3 axis = Vector3::Cross(Vector3::Up, mp);
	
	//���݂̃J������Up����ɂ��āA�񎟌��x�N�g���������@���l����
	/*
	mp = mp*Matrix::CreateFromAxisAngle(axis, -angle);

	//auto i = Matrix::InvertFast(Matrix(Matrix::Identity).Up(mp).NormalizeRotationMatrix());
	mp.z = 0.0f;
	mp = mp*Matrix::CreateFromAxisAngle(axis, angle);
	
	//mp-=upVector_;
	
	*/

	movefwPos_ = -mp;
	moverhPos_ = Vector3::Cross(mp, upVector_);
	position_ = Vector3::Lerp(position_,target_.lock()->getPosition() + movePos,0.9f);
	Camera::GetInstance().Position.Set(position_);
	Camera::GetInstance().Target.Set(target_.lock()->getPosition() + moveTargetPos_);
	Camera::GetInstance().Up.Set(upVector_);
	Camera::GetInstance().Update();


}

void CameraActor::draw() const
{
}

void CameraActor::end()
{
}

void CameraActor::setTarget(const std::shared_ptr<Actor>& target)
{
	target_ = target;
}

void CameraActor::setUpVector(const Vector3 & up)
{
	upVector_ = up;
}
