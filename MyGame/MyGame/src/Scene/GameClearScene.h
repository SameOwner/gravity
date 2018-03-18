#pragma once
#include"Scene.h"

class GameClearScene :public Scene {
public:
	GameClearScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEndがtrueになった後の処理
	virtual void end() override;

private:
	int sinCount_{ 0 };//点滅カウント

};