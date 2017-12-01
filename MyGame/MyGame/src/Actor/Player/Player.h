#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include<map>

class Player:public Actor {
public:
	enum class Player_State {
		Idle,//�ҋ@
		Jump,//�W�����v
		Slide,//����
		SlideJump,//����W�����v
		Float,//���V
		Fly,//��s
		WallRun,//�Ǔ\���
		FloatJump,//�Ǔ\����W�����v
		FloatFall,//�Ǔ\�������
		Fall,//����
	};
	enum class Player_Animation {
		Idle=0,
		Jump=0,
		Slide=0,
		SlideJump=0,
		Float=0,
		Fly=0,
		WallRun=0,
		FloatJump = 0,
		FloatFall = 0,
		Fall=0,

	};
public:
	Player(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,0.0f,0.0f},Matrix::Identity,15.0f,4.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;

	//�󒆎���x,z�̈ړ��x�N�g����傫������
	void aerialVelocityKeep();
	void floatVelocityKeep();
private:

	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);
	//��Ԃ̍X�V
	bool change_State(Player_State state);
	//�A�j���[�V�����̕ύX
	void change_Animation(Player_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true);

	//�d�͒l�̉��Z
	void addGravity();

	//�d�͒l(�d�͕ω���)�̉��Z
	void addFloatGravity();

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

	void to_Slide();
	void update_Slide(float deltaTime);
	void end_Slide();

	//�W�����v
	void to_Jump();
	void update_Jump(float deltaTime);
	void end_Jump();

	//���V�W�����v
	void to_SlideJump();
	void update_SlideJump(float);
	void end_SlideJump();

	//���V
	void to_Float();
	void update_Float(float deltaTime);
	void end_Float();

	//��s
	void to_Fly();
	void update_Fly(float deltaTime);
	void end_Fly();

	//�Ǔ\���
	void to_WallRun();
	void update_WallRun(float deltaTime);
	void end_WallRun();

	//�ǃW�����v
	void to_FloatJump();
	void update_FloatJump(float deltaTime);
	void end_FloatJump();

	//�ǃW�����v
	void to_FloatFall();
	void update_FloatFall(float deltaTime);
	void end_FloatFall();

	//����
	void to_Fall();
	void update_Fall(float deltaTime);
	void end_Fall();

	
private:
	AnimationDx animation_;
	//���g�̏��
	Player_State state_;
	//�d�͔{��
	float gravity_{ 0.0f };
	
	//��s����
	Vector3 flyDirection_{ Vector3::Zero };
	//�O�t�����ɂ��Ă���
	bool prevfloor_{ false };

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;
};