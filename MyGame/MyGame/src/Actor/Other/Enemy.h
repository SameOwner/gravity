#pragma once
#include"../Actor.h"
#include"../Body/BoundingCapsule.h"

class Enemy :public Actor {
private:
	enum class State {
		Idle,
		Move,
		Attack
	};
public:
	Enemy(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	void initialize() override;

	void setTarget_Player();//プレイヤーをターゲットにする
	void update(float deltaTime) override;

	void draw()const override;


private:
	std::weak_ptr<Actor> target_;
};