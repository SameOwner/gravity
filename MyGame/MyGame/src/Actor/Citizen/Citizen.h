#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include"../../ID/EnumIDs.h"
#include"CityWalkPointChooser.h"
#include<map>

class Citizen:public Actor {
private:
	enum class State {
		Idle,
		Walk,
		Down
	};
	enum class Animation {
		Idle = 0,
		Walk = 1,
		Down = 2,
	};
	struct AnimStyle {
		AnimStyle(bool isloop, Animation anim) :isLoop(isloop), animation(anim) {

		}
		bool isLoop;
		Animation animation;
	};
public:
	Citizen(IWorld* world,const Vector3& position,MODEL_ID id,int type, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	//���S��
	virtual void end();
	//�ڐG��
	virtual void onCollide(Actor& other) override;

	void change_Animation(Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blendRate = 1.0f);
	void change_State(State state);
private:
	void idle(float deltaTime);
	void walk(float deltaTime);
	void down(float deltaTime);
private:
	AnimationDx animation_;//���f���y�уA�j���[�V�����̊Ǘ�

	MODEL_ID modelid_;//�g�p���f����ID

	State state_;//���

	CityWalkPointChooser chooser_;//�ړ��挈��

	float timer_{ 10.0f };
	const std::map<State, AnimStyle> AnimConverter{//�X�e�[�g�ƃA�j���[�V�����̊֘A�t��
		{State::Idle,AnimStyle{false,Animation::Idle}},
		{State::Walk,AnimStyle{true,Animation::Walk}},
		{State::Down,AnimStyle{false,Animation::Down}}
	};
};