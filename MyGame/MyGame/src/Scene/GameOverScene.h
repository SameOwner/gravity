#pragma once
#include"Scene.h"

class GameOverScene :public Scene{
public:
	GameOverScene();
	~GameOverScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEnd‚ªtrue‚É‚È‚Á‚½Œã‚Ìˆ—
	virtual void end() override;


private:

};