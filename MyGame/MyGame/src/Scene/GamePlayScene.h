#pragma once
#include"Scene.h"

#include"../World/World.h"

class Player;
//シーンテンプレート
class GamePlayScene:public Scene {
public:
	GamePlayScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEndがtrueになった後の処理
	virtual void end() override;

private:
	World world_;
	std::shared_ptr<Player> player_;
};