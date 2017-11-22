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
	//前方向移動ベクトルを取得する
	Vector3 getMoveForwardPos()const { return movefwPos_; }
	//横方向移動ベクトルを取得する
	Vector3 getMoveRightPos()const { return moverhPos_; }
	//カメラの前方ベクトルを取得する
	Vector3 getCameraForwardPos()const { return camerafwPos_; }
	//ターゲットの指定
	void setTarget(const std::shared_ptr<Actor>& target);
	//回転行列を設定する
	void setUpVector(const Vector3& up);
private:
	//追跡対象
	std::weak_ptr<Actor> target_;
	//カメラの有効無効
	bool isActive_{ true };
	//キャラクターとカメラの距離
	float cameraDistance_{ 0.0f };
	//カメラを基準とした前移動ベクトル
	Vector3 movefwPos_{ Vector3::Zero };
	//カメラを基準とした横移動ベクトル
	Vector3 moverhPos_{ Vector3::Zero };
	Vector3 camerafwPos_{ Vector3::Zero };
	//カメラの回転
	Vector2 rotate_{ Vector2::Zero };
	//注目する位置を動かすベクトル
	Vector3 moveTargetPos_{ Vector3::Zero };
	Vector3 upVector_{ Vector3::Up };
	//補正ベクトル
	Vector3 correctPos_{ Vector3{0.0f,5.0f,0.0f} };
};