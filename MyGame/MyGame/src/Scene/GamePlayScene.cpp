#include "GamePlayScene.h"
#include"../Actor/Actors.h"
#include"../Graphic/Model.h"
#include"../Field/FieldBase.h"
#include"../Input/InputChecker.h"
#include"../Define.h"
#include"../Graphic/Sprite.h"

GamePlayScene::GamePlayScene():world_(),player_(nullptr), pointGenerator_()/*,cc{&world_,Vector3::Zero}*/
{
}

void GamePlayScene::start()
{
	world_.initialize();
	world_.setField(std::make_shared<FieldBase>(Model::GetInstance().GetHandle(MODEL_ID::MODEL_STAGE), Model::GetInstance().GetHandle(MODEL_ID::MODEL_SKYBOX)));
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");
	pointGenerator_.setParameter(&world_, "res/Data/point.csv");

	player_ = std::make_shared<Player>(&world_, Vector3{ 0,10.0f,0 });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);

	//auto point = std::make_shared<CheckPoint>(&world_, Vector3{ 0.0f,5.0f,10.0f });
	//world_.addActor(ActorGroup::POINT_ACTOR , point);
	auto car = std::make_shared<Car>(&world_, Vector3{ 835.f,0.0f,-95.f }, MODEL_ID::MODEL_CAR);
	world_.addActor(ActorGroup::CAR_ACTOR, car);
	//cc.setTarget(car);

	auto camera = std::make_shared<CameraActor>(&world_, player_->getPosition());
	world_.addCamera(camera);
	camera->setTarget(player_);

}

void GamePlayScene::update(float deltaTime)
{
	world_.update(deltaTime);

	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::Start)) {
		isEnd_ = true;
		next_ = SceneType::SCENE_TITLE;
	}

	pointGenerator_.update(deltaTime);

	if (pointGenerator_.isEnd()) {
		isEnd_ = true;
		next_ = SceneType::SCENE_CLEAR;
	}
	//cc.update(deltaTime);
}

void GamePlayScene::draw() const
{
	world_.draw();

	pointGenerator_.draw();

	//DrawCircleGauge(50, 50, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::SPRITE_FLOATGAUGE));
}

void GamePlayScene::end()
{
}
