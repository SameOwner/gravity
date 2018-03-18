#pragma once
#include"Scene.h"

//シーンテンプレート
class TitleScene :public Scene {
public:
	TitleScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEndがtrueになった後の処理
	virtual void end() override;

private:
	int sinCount_{ 0 };//点滅カウント
};