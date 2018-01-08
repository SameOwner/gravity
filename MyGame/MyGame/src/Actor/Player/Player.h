#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationOutSide.h"
#include"../Body/BoundingCapsule.h"
#include"../../Effect/SpriteEffect/CameraWind.h"
#include"../../Method/CountTimer.h"

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
		Blow,//������΂�
		Down,//�]��
		GetUp,//�N���オ��
	};
	enum class Player_Animation {
		Idle=0,
		Run=1,
		Jump=3,
		Slide=5,
		SlideJump=3,
		Float=3,
		Blow=7,
		Down = 8,
		GetUp = 9,
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

	//�󒆎���x,z�̈ړ��x�N�g����傫������
	void aerialVelocityKeep();
	void floatVelocityKeep();

	void hit(const Vector3& direction);

	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

private:

	//��ԕύX�ƃA�j���[�V�����ύX�𓯎��ɍs��
	bool change_State_and_Anim(Player_State state, Player_Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true);
	//��Ԃ̍X�V
	bool change_State(Player_State state);
	//�A�j���[�V�����̕ύX
	void change_Animation(Player_Animation animID, float animFrame = 0.0f, float animeSpeed = 1.0f, bool isLoop = true, float blendRate=1.0f);

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

	//������΂�
	void to_Blow();
	void update_Blow(float deltaTime);
	void end_Blow();

	//�_�E��
	void to_Down();
	void update_Down(float deltaTime);
	void end_Down();

	//�N���オ��
	void to_GetUp();
	void update_GetUp(float deltaTime);
	void end_GetUp();

	//���V�Q�[�W����(0�ȉ��ɂȂ�����false��Ԃ�)
	bool subFloatPower();
private:
	//�ő啂�V�Q�[�W�l
	const float MaxFloatPower{ 100.0f };
	//��{�I��velocity�̏�Z����
	const float DefVelocityMult{ 0.8f };
	AnimationOutSide animation_;
	//���g�̏��
	Player_State state_;
	//�d�͔{��
	float gravity_{ 0.0f };
	
	//���V�Q�[�W
	float floatPower_;

	//��s����
	Vector3 flyDirection_{ Vector3::Zero };
	//�O�t�����ɂ��Ă���
	bool prevfloor_{ false };

	float velocityMultPower{ DefVelocityMult };

	//������΂�����
	Vector3 blowDirection_{ Vector3::Zero };
	CountTimer downTimer_{};

	std::map<Player_State, std::function<void(float)>> playerUpdateFunc_;
	std::map<Player_State, std::function<void()>> playerEndModeFunc_;
	std::map<Player_State, std::function<void()>> playerToNextModeFunc_;

private:
	CameraWind wind_;
};