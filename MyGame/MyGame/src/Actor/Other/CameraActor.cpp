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
	setUpVector(Vector3::Up);
	target_.reset();
	Camera::GetInstance().SetRange(0.1f, 1000.0f);
	Camera::GetInstance().SetViewAngle(60.0f);
}

void CameraActor::update(float deltaTime)
{
	Vector3 movePos = Vector3::Zero;//���t���[���p�̃J�����ړ��x�N�g��

	//���͂�����Ă���
	Vector2 move = InputChecker::GetInstance().RightStick()*3.f;
	if (move.Length() > 0.2f) {
		rotate_ += move;
		//�J�����̉�]���E��ݒ肷��
		rotate_.y = MathHelper::Clamp(rotate_.y, -80.0f, 80.0f);
	}

	//���ʍ��W����Ƃ����ʒu�␳���s��
	movePos.x = -cameraDistance_*MathHelper::Sin(rotate_.x) * MathHelper::Cos(rotate_.y);
	movePos.y = -cameraDistance_*MathHelper::Sin(rotate_.y);
	movePos.z = -cameraDistance_*MathHelper::Cos(rotate_.x) * MathHelper::Cos(rotate_.y);

	
	//�v���C���[�p�̐ݒ�
	camerafwPos_ = (-movePos).Normalize();

	//�����𒲂ׂāA����ɉ�������]�ʂɂ��Ă�����K�v������
	float dot = Vector3::Dot(Vector3::Up, upVector_);
	Vector3 axis = Vector3::Cross(Vector3::Up, upVector_);

	//movePos����]�����āA������Up�x�N�g���ɍ��킹��
	float angle = MathHelper::ACos(dot);
	movePos = movePos* Matrix::CreateFromAxisAngle(axis, angle);


	//�v���C���[�p�̐ݒ�
	Vector3 mp = movePos;
	mp.Normalize();
	Vector3 left = Vector3::Normalize(Vector3::Cross(upVector_, mp));
	Vector3 backward = Vector3::Cross(left, upVector_);

	//�ړ�����ݒ肷��
	movefwPos_ = -backward;
	moverhPos_ = -left;


	//�ʒu��Ԃ��s��
	position_ = Vector3::Lerp(position_,target_.lock()->getPosition() + movePos,0.9f);

	//�J�����ʒu���Z�b�g����
	Camera::GetInstance().Position.Set(position_);
	Camera::GetInstance().Target.Set(target_.lock()->getPosition() + moveTargetPos_);
	Camera::GetInstance().Up.Set(upVector_);
	Camera::GetInstance().Update();


}

void CameraActor::draw() const
{
	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + test, GetColor(255, 0, 0));
	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + rotation_.Up(), GetColor(0, 255, 0));
	//DrawLine3D(target_.lock()->getPosition(), target_.lock()->getPosition() + rotation_.Forward(), GetColor(0, 0, 255));
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
	//rotation_.Up(up);
	//rotation_.NormalizeRotationMatrix_BaseUp();
}

Vector3 CameraActor::getUpVector() const
{
	return upVector_;
}
