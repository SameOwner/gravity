#pragma once
#include"Scene.h"
#include"../Field/PointGenerator.h"
#include"../World/World.h"
//#include"../Actor/Other/CarCamera.h"

class Player;
//�V�[���e���v���[�g
class GamePlayScene:public Scene {
public:
	GamePlayScene();
	~GamePlayScene() = default;

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() override;

private:
	PointGenerator pointGenerator_;
	World world_;
	std::shared_ptr<Player> player_;
	//CarCamera cc;

};