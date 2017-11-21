#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include<map>

class Player:public Actor {
public:
	enum class Player_State {
		Idle,//待機
		Float,//浮遊
		Fly,//飛行
		Fall,//落下
	};
	enum class Player_Animation {
		Idle=0,
		Float=0,
		Fly=0,
		Fall=0,

	};
public:
	Player(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,0.0f,0.0f},Matrix::Identity,15.0f,4.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;


private:

	//状態変更とアニメーション変更を同時に行う
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);
	//状態の更新
	bool change_State(Player_State state);
	//アニメーションの変更
	void change_Animation(Player_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true);

//状態関数
private:
	//待機
	void to_Idle();
	void update_Idle(float deltaTime);
	void end_Idle();

	//移動
	void to_Move();
	void update_Move(float deltaTime);
	void end_Move();

	//浮遊
	void to_Float();
	void update_Float(float deltaTime);
	void end_Float();

	//飛行
	void to_Fly();
	void update_Fly(float deltaTime);
	void end_Fly();

	//落下
	void to_Fall();
	void update_Fall(float deltaTime);
	void end_Fall();
private:
	AnimationDx animation_;
	//自身の状態
	Player_State state_;
	//重力倍率
	float gravity_{ 0.0f };
	
	//飛行方向
	Vector3 flyDirection_{ Vector3::Zero };
	//前フレ床についてたか
	bool prevfloor_{ false };

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;


};