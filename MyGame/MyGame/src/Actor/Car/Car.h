#pragma once
#include"../Actor.h"
#include"../Body/BoundingCapsule.h"
#include"../../ID/EnumIDs.h"
#include"PointChooser.h"

//’¬‚ğ„‰ñ‚·‚éÔƒNƒ‰ƒX
class Car :public Actor {
private:
	enum class Stete {
		Idle,
		Move
	};
public:
	Car(IWorld* world, const Vector3& position, MODEL_ID id, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix(Matrix::Identity)*Matrix::CreateRotationX(90.0f), 70.0f, 25.0f));

	void update(float deltaTime);

	void draw()const;

	//ÚG
	virtual void onCollide(Actor& other);
private:
	MODEL_ID modelid_;
	PointChooser chooser_;

	Vector3 nextPoint_;
};