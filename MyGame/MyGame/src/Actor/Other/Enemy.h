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

	void setTarget_Player();//�v���C���[���^�[�Q�b�g�ɂ���
	void update(float deltaTime) override;

	void draw()const override;

	void onCollide(Actor& other) override;

	bool checkAttack();//�U���\���̃`�F�b�N

	void idle(float deltaTime);
	void move(float deltaTime);
	void aim(float deltaTime);
	void attack(float deltaTime);

	void changeState(State state, bool isLoop=true);
private:
	std::weak_ptr<Actor> target_;//�U���Ώ�

	State state_;//���

	AnimationDx animation_;//�A�j���[�V����

	const std::map<State, int> animHandleConv{
		{ State::Idle,0 },
		{ State::Move,0 },
		{ State::Aim,0 },
		{ State::Attack,1 }
	};
	PointChooser chooser_;//�ړ��挈��
	Vector3 nextPoint_;//�ړI�n

	CountTimer timer_;//�Ăяo���J�E���g
	
	CountTimer coolTime_;//�U���p�N�[���^�C���J�E���g

};