#pragma once
#include"../Actor.h"
#include"../../Method/CallBackTimer.h"

class EnemyBullet:public Actor {
public:
	EnemyBullet(IWorld* world,const Vector3& position,const Vector3& velocity);

	void update(float deltaTime)override;

	void draw()const override;

	void onCollide(Actor& other)override;
private:
	Vector3 velocity_;//進行方向

	CallBackTimer timer_;//タイマー
};