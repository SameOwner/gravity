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
	//ターゲットの指定
	void setTarget(const std::shared_ptr<Actor>& target);
private:
	//追跡対象
	std::weak_ptr<Actor> target_;
	//カメラの有効無効
	bool isActive_{ true };
	//キャラクターとカメラの距離
	float cameraDistance_{ 0.0f };
	//カメラの回転
	Vector2 rotate_{ Vector2::Zero };
	//注目する位置を動かすベクトル
	Vector3 moveTargetPos_{ Vector3::Zero };
};