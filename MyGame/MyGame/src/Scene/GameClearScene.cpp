#include "GameClearScene.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Input/InputChecker.h"

GameClearScene::GameClearScene()
{
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::start()
{
	isEnd_ = false;
	next_ = SceneType::SCENE_TITLE;

}


void GameClearScene::update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		isEnd_ = true;
	}

}

void GameClearScene::draw() const
{
	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "ÉNÉäÉA");

}

void GameClearScene::end()
{
}
