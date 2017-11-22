#pragma once
#include"../../Camera/Camera.h"
#include"../Actor.h"
#include"../Body/BoundingSphere.h"

class CameraActor :public Actor {
public:
	CameraActor(IWorld* world, const Vector3& position, IBodyPtr body = std::make_shared<BoundingSphere>(Vector3{ 0.0f,0.0f,0.0f }, 5.0f));

	virtual void initialize()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void end()override;
	//�O�����ړ��x�N�g�����擾����
	Vector3 getMoveForwardPos()const { return movefwPos_; }
	//�������ړ��x�N�g�����擾����
	Vector3 getMoveRightPos()const { return moverhPos_; }
	//�J�����̑O���x�N�g�����擾����
	Vector3 getCameraForwardPos()const { return camerafwPos_; }
	//�^�[�Q�b�g�̎w��
	void setTarget(const std::shared_ptr<Actor>& target);
	//��]�s���ݒ肷��
	void setUpVector(const Vector3& up);
private:
	//�ǐՑΏ�
	std::weak_ptr<Actor> target_;
	//�J�����̗L������
	bool isActive_{ true };
	//�L�����N�^�[�ƃJ�����̋���
	float cameraDistance_{ 0.0f };
	//�J��������Ƃ����O�ړ��x�N�g��
	Vector3 movefwPos_{ Vector3::Zero };
	//�J��������Ƃ������ړ��x�N�g��
	Vector3 moverhPos_{ Vector3::Zero };
	Vector3 camerafwPos_{ Vector3::Zero };
	//�J�����̉�]
	Vector2 rotate_{ Vector2::Zero };
	//���ڂ���ʒu�𓮂����x�N�g��
	Vector3 moveTargetPos_{ Vector3::Zero };
	Vector3 upVector_{ Vector3::Up };
	//�␳�x�N�g��
	Vector3 correctPos_{ Vector3{0.0f,5.0f,0.0f} };
};