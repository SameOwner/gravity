#pragma once
#include<map>
#include"../Actor.h"
#include"../Body/BoundingCapsule.h"
#include"../../Graphic/AnimationDx.h"
#include"../Car/PointChooser.h"
#include"../../Method/CountTimer.h"

class Enemy :public Actor {
private:
	enum class State {
		Idle,
		Move,
		Aim,
		Attack
	};
public:
	Enemy(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 5.0f, 4.0f));
	void initialize() override;

	void setTarget_Player();//プレイヤーをターゲットにする
	void update(float deltaTime) override;

	void draw()const override;

	void onCollide(Actor& other) override;

	bool checkAttack();//攻撃可能かのチェック

	void idle(float deltaTime);
	void move(float deltaTime);
	void aim(float deltaTime);
	void attack(float deltaTime);

	void changeState(State state, bool isLoop=true);
private:
	std::weak_ptr<Actor> target_;//攻撃対象

	State state_;//状態

	AnimationDx animation_;//アニメーション

	const std::map<State, int> animHandleConv{
		{ State::Idle,0 },
		{ State::Move,0 },
		{ State::Aim,0 },
		{ State::Attack,1 }
	};
	PointChooser chooser_;//移動先決定
	Vector3 nextPoint_;//目的地

	CountTimer timer_;//呼び出しカウント
	
	CountTimer coolTime_;//攻撃用クールタイムカウント

};