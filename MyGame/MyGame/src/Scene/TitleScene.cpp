#include "TitleScene.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Input/InputChecker.h"

TitleScene::TitleScene()
{
}

void TitleScene::start()
{
	isEnd_ = false;
	next_ = SceneType::SCENE_GAMEPLAY;
}

void TitleScene::update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		isEnd_ = true;
	}
}

void TitleScene::draw() const
{
	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH/2,WINDOW_HEIGHT/2,GetColor(255,255,255),"〇でスタート");
}

void TitleScene::end()
{
}
