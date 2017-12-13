#include "GameOverScene.h"
#include"../Input/InputChecker.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"

GameOverScene::GameOverScene()
{
	next_ = SceneType::SCENE_TITLE;
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::start()
{
	isEnd_ = false;

}

void GameOverScene::update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		isEnd_ = true;
	}

}

void GameOverScene::draw() const
{
	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "ゲームオーバー");

}

void GameOverScene::end()
{
}
