#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include<map>

class Player:public Actor {
public:
	enum class Player_State {
		Idle,
	};
	enum class Player_Animation {
		Idle,
	};
public:
	Player(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,0.0f,0.0f},Matrix::Identity,20.0f,5.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;


private:

	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);
	//��Ԃ̍X�V
	bool change_State(Player_State state);
	//�A�j���[�V�����̕ύX
	void change_Animation(Player_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true);

//��Ԋ֐�
private:
	//�ҋ@
	void to_Idle();
	void update_Idle(float deltaTime);
	void end_Idle();

	//�ړ�
	void to_Move();
	void update_Move(float deltaTime);
	void end_Move();

private:
	AnimationDx animation_;
	//���g�̏��
	Player_State state_;


	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;


};