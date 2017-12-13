#pragma once
#include"Scene.h"

class GameOverScene :public Scene{
public:
	GameOverScene();
	~GameOverScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEndがtrueになった後の処理
	virtual void end() override;


private:

};