#include "GamePlayScene.h"
#include"../Actor/Actors.h"
#include"../Graphic/Model.h"
#include"../Field/FieldBase.h"

GamePlayScene::GamePlayScene():world_(),player_(nullptr)
{
}

void GamePlayScene::start()
{
	world_.initialize();

	world_.setField(std::make_shared<FieldBase>(Model::GetInstance().GetHandle(MODEL_ID::MODEL_STAGE), Model::GetInstance().GetHandle(MODEL_ID::MODEL_SKYBOX)));

	player_ = std::make_shared<Player>(&world_, Vector3{ 0,10.0f,0 });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);

	auto camera = std::make_shared<CameraActor>(&world_, player_->getPosition());
	world_.addCamera(camera);
	camera->setTarget(player_);
}

void GamePlayScene::update(float deltaTime)
{
	world_.update(deltaTime);
}

void GamePlayScene::draw() const
{
	world_.draw();
}

void GamePlayScene::end()
{
}
