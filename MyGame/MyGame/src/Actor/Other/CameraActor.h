#pragma once
#include"../../Camera/Camera.h"
#include"../Actor.h"
#include"../Body/BoundingSphere.h"

class CameraActor :public Actor {
public:
	CameraActor(IWorld* world, IBodyPtr body = std::make_shared<BoundingSphere>(Vector3{ 0.0f,0.0f,0.0f }, 5.0f));

	virtual void initialize()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void end()override;
	//�^�[�Q�b�g�̎w��
	void setTarget(std::shared_ptr<Actor>& target);
private:
	//�ǐՑΏ�
	std::weak_ptr<Actor> target_;
	//�J�����̗L������
	bool isActive_{ true };
};