#pragma once
#include"Scene.h"

class GameClearScene :public Scene {
public:
	GameClearScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd��true�ɂȂ�����̏���
	virtual void end() override;

private:
	int sinCount_{ 0 };//�_�ŃJ�E���g

};