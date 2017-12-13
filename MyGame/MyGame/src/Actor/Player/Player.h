#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationOutSide.h"
#include"../Body/BoundingCapsule.h"
#include"../../Effect/SpriteEffect/CameraWind.h"

#include<map>

class Player:public Actor {
public:
	enum class Player_State {
		Idle,//待機
		Jump,//ジャンプ
		Slide,//滑り
		SlideJump,//滑りジャンプ
		Float,//浮遊
		Fly,//飛行
		WallRun,//壁貼りつき
		FloatJump,//壁貼りつきジャンプ
		FloatFall,//壁貼りつき落下
		Fall,//落下
	};
	enum class Player_Animation {
		Idle=0,
		Run=1,
		Jump=3,
		Slide=5,
		SlideJump=3,
		Float=3,
		Fly=6,
		WallRun=1,
		FloatJump = 3,
		FloatFall = 3,
		Fall=3,

	};

public:
	Player(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,0.0f,0.0f},Matrix::Identity,15.0f,4.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;

	//空中時はx,zの移動ベクトルを大きくする
	void aerialVelocityKeep();
	void floatVelocityKeep();
private:

	//状態変更とアニメーション変更を同時に行う
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);
	//状態の更新
	bool change_State(Player_State state);
	//アニメーションの変更
	void change_Animation(Player_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true, float blendRate=1.0f);

	//重力値の加算
	void addGravity();

	//重力値(重力変化時)の加算
	void addFloatGravity();

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

	void to_Slide();
	void update_Slide(float deltaTime);
	void end_Slide();

	//ジャンプ
	void to_Jump();
	void update_Jump(float deltaTime);
	void end_Jump();

	//浮遊ジャンプ
	void to_SlideJump();
	void update_SlideJump(float);
	void end_SlideJump();

	//浮遊
	void to_Float();
	void update_Float(float deltaTime);
	void end_Float();

	//飛行
	void to_Fly();
	void update_Fly(float deltaTime);
	void end_Fly();

	//壁貼りつき
	void to_WallRun();
	void update_WallRun(float deltaTime);
	void end_WallRun();

	//壁ジャンプ
	void to_FloatJump();
	void update_FloatJump(float deltaTime);
	void end_FloatJump();

	//壁ジャンプ
	void to_FloatFall();
	void update_FloatFall(float deltaTime);
	void end_FloatFall();

	//落下
	void to_Fall();
	void update_Fall(float deltaTime);
	void end_Fall();

	//浮遊ゲージ減少(0以下になったらfalseを返す)
	bool subFloatPower();
private:
	//最大浮遊ゲージ値
	const float MaxFloatPower{ 100.0f };
	//基本的なvelocityの乗算割合
	const float DefVelocityMult{ 0.8f };
	AnimationOutSide animation_;
	//自身の状態
	Player_State state_;
	//重力倍率
	float gravity_{ 0.0f };
	
	//浮遊ゲージ
	float floatPower_;

	//飛行方向
	Vector3 flyDirection_{ Vector3::Zero };
	//前フレ床についてたか
	bool prevfloor_{ false };

	float velocityMultPower{ DefVelocityMult };

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

private:
	CameraWind wind_;
};