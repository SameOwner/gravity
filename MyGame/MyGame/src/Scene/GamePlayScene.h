#pragma once
#include"Scene.h"
#include"../Field/PointGenerator.h"
#include"../World/World.h"

class Player;
//シーンテンプレート
class GamePlayScene:public Scene {
public:
	GamePlayScene();
	~GamePlayScene() = default;

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	//isEndがtrueになった後の処理
	virtual void end() override;

private:
	PointGenerator pointGenerator_;
	World world_;
	std::shared_ptr<Player> player_;
};