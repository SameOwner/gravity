#include "TitleScene.h"

TitleScene::TitleScene()
{
}

void TitleScene::start()
{
	isEnd_ = true;
	next_ = SceneType::SCENE_GAMEPLAY;
}

void TitleScene::update(float deltaTime)
{
}

void TitleScene::draw() const
{
}

void TitleScene::end()
{
}
