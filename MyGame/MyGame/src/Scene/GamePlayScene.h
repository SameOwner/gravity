#pragma once
#include"Scene.h"

#include"../World/World.h"
#include"../Actor/Player/Player.h"

//�V�[���e���v���[�g
class GamePlayScene:public Scene {
public:
	GamePlayScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() override;

private:
	World world_;
	std::shared_ptr<Player> player_;
};