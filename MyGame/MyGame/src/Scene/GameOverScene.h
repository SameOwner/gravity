#pragma once
#include"Scene.h"

class GameOverScene :public Scene{
public:
	GameOverScene();
	~GameOverScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() override;


private:

};