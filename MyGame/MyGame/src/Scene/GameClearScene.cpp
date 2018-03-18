#include "GameClearScene.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Input/InputChecker.h"
#include"../Graphic/Sprite.h"
#include"../Math/MathHelper.h"
#include"../Sound/Sound.h"

GameClearScene::GameClearScene()
{
}

void GameClearScene::start()
{
	isEnd_ = false;
	next_ = SceneType::SCENE_TITLE;
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_CLEAR, DX_PLAYTYPE_LOOP);

}


void GameClearScene::update(float deltaTime)
{
	if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
		isEnd_ = true;
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::SELECT_SE);

	}
	sinCount_ = (sinCount_ + 1) % 360;

}

void GameClearScene::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_TITLEBACK, Vector2::Zero);
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GAMECLEAR, Vector2(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.2f), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_TITLELOGO))*0.5f, Vector2::One);
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_TITLEBUTTON, Vector2(WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.7f), Vector2(Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_TITLEBUTTON))*0.5f, MathHelper::Abs(MathHelper::Sin((float)sinCount_)), Vector2::One);

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "ÉNÉäÉA");

}

void GameClearScene::end()
{
	Sound::GetInstance().StopBGM();

}
