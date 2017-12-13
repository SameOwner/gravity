#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationOutSide.h"
#include"../Body/BoundingCapsule.h"

class Citizen:public Actor {
private:
	enum class State {
		Idle,
		Walk
	};
	enum class Animation {
		Idle = 0,
		Walk = 1
	};
public:
	Citizen(IWorld* world,const Vector3& position,MODEL_ID id, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	//éÄñSéû
	virtual void end();
	//ê⁄êGéû
	virtual void onCollide(Actor& other);

	void change_Animation(Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blendRate = 1.0f);

private:
	AnimationOutSide animation_;

	MODEL_ID modelid_;
};