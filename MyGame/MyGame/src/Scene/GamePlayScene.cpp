#include "GamePlayScene.h"

GamePlayScene::GamePlayScene():world_(),player_(nullptr)
{
}

void GamePlayScene::start()
{
	world_.initialize();

	player_ = std::make_shared<Player>(&world_, Vector3{ 0,0,0 });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);
}

void GamePlayScene::update(float deltaTime)
{
}

void GamePlayScene::draw() const
{
}

void GamePlayScene::end()
{
}
