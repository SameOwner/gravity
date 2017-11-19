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
	//�^�[�Q�b�g�̎w��
	void setTarget(const std::shared_ptr<Actor>& target);
private:
	//�ǐՑΏ�
	std::weak_ptr<Actor> target_;
	//�J�����̗L������
	bool isActive_{ true };
	//�L�����N�^�[�ƃJ�����̋���
	float cameraDistance_{ 0.0f };
	//�J�����̉�]
	Vector2 rotate_{ Vector2::Zero };
	//���ڂ���ʒu�𓮂����x�N�g��
	Vector3 moveTargetPos_{ Vector3::Zero };
};