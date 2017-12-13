#pragma once
#include"Scene.h"

class GameClearScene :public Scene {
public:
	GameClearScene();
	~GameClearScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd‚ªtrue‚É‚È‚Á‚½Œã‚Ìˆ—
	virtual void end() override;

};