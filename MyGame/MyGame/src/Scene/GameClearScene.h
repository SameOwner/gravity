#pragma once
#include"Scene.h"

class GameClearScene :public Scene {
public:
	GameClearScene();
	~GameClearScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() override;

};