#pragma once

#include <DxLib.h>

#include "Time.h"
#include "../Input/InputChecker.h"
#include "../Math/Math.h"
#include"../Camera/Camera.h"
#include"../Input/GamePad.h"
#include"../Graphic/EffekseerManager.h"
#include"../Scene/SceneManager.h"

class MyGame {
public:
	// コンストラクタ
	MyGame(const Vector2& screen_size = Vector2(800, 600), float rate = 1.0f, int window = TRUE, float fps = 60.0f) :
		mWidth(static_cast<int>(screen_size.x)), mHeight(static_cast<int>(screen_size.y)), mRate(rate), mWindow(window), mFps(fps), sceneManager_(){
	}
	~MyGame(){}
public:
	// 実行
	int run() {
		// サイズ指定
		SetGraphMode(mWidth, mHeight, 32);
		// 描画倍率
		SetWindowSizeExtendRate(mRate);
		// ウインドウモードにするかどうか
		ChangeWindowMode(mWindow);
		SetUseDirect3DVersion(DX_DIRECT3D_9);
		//DXLib初期化処理
		if (DxLib_Init() == -1)return -1;//エラーが起きたら終了
		SetDrawScreen(DX_SCREEN_BACK);
		SetUseBackCulling(TRUE);
		SetAlwaysRunFlag(TRUE);//デバッグ用
		start();

		// キーが押されるまでループします
		while (isRunning()) {
			etceteraUpdate();

			update();
			draw();
			frameEnd();
			//Time::GetInstance().draw_fps();
			// 裏画面の内容を表画面に反映させる
			ScreenFlip();
		}

		end();

		//DXLib使用終了処理
		DxLib_End();

		return 0;	//ソフト終了
	}

private:
	// 開始
	void start() {
		sceneManager_.start();
	}
	// 更新
	void update() {
		sceneManager_.update(Time::GetInstance().deltaTime());
	}
	// 描画
	void draw() {
		sceneManager_.draw();
	}
	//フレーム終了時処理
	void frameEnd() {
		sceneManager_.checkIsEnd();
	}
	// 終了
	void end() {

	}
	// 実行中か
	bool isRunning() { return (ProcessMessage() == 0 && ClearDrawScreen() == 0 && Keyboard::GetInstance().KeyStateUp(KEYCODE::ESC)); }

	void etceteraUpdate() {
		//deltaTimeの更新
		Time::GetInstance().update();
		//入力の更新
		InputChecker::GetInstance().Update();
		//入力更新
		GamePad::GetInstance().Update();

	}
	// コピー禁止
	MyGame(const MyGame& other) = delete;
	MyGame& operator = (const MyGame& other) = delete;

private:
	// ウィンドウの幅
	int mWidth;
	// ウィンドウの高さ
	int mHeight;
	// ウインドウの描画比率
	float mRate;
	// ウインドウモードか？
	int mWindow;
	// FPS
	float mFps;
	//シーン管理クラス
	SceneManager sceneManager_;
};