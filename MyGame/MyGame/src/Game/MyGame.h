#pragma once

#include <DxLib.h>
#include "Time.h"
#include "../Input/InputChecker.h"
#include "../Math/Math.h"
#include"../Camera/Camera.h"
#include"../Input/DualShock4Manager.h"
#include"../Graphic/EffekseerManager.h"
#include"../Scene/SceneManager.h"

class MyGame {
public:
	// �R���X�g���N�^
	MyGame(const Vector2& screen_size = Vector2(800, 600), float rate = 1.0f, int window = TRUE, float fps = 60.0f) :
		mWidth(static_cast<int>(screen_size.x)), mHeight(static_cast<int>(screen_size.y)), mRate(rate), mWindow(window), mFps(fps), sceneManager_(){
	}
	~MyGame(){}
public:
	// ���s
	int run() {
		// �T�C�Y�w��
		SetGraphMode(mWidth, mHeight, 32);
		// �`��{��
		SetWindowSizeExtendRate(mRate);
		// �E�C���h�E���[�h�ɂ��邩�ǂ���
		ChangeWindowMode(mWindow);
		SetUseDirect3DVersion(DX_DIRECT3D_9);
		//DXLib����������
		if (DxLib_Init() == -1)return -1;//�G���[���N������I��
		SetDrawScreen(DX_SCREEN_BACK);
		SetUseBackCulling(TRUE);
		EffekseerManager::GetInstance().Initialize();

		start();

		// �L�[���������܂Ń��[�v���܂�
		while (isRunning()) {
			etceteraUpdate();

			update();
			draw();
			frameEnd();
			//Time::GetInstance().draw_fps();
			// ����ʂ̓��e��\��ʂɔ��f������
			ScreenFlip();
		}

		end();

		//DXLib�g�p�I������
		DxLib_End();

		return 0;	//�\�t�g�I��
	}

private:
	// �J�n
	void start() {
		sceneManager_.start();
	}
	// �X�V
	void update() {
		sceneManager_.update(Time::GetInstance().deltaTime());
	}
	// �`��
	void draw() {
		sceneManager_.draw();
	}
	//�t���[���I��������
	void frameEnd() {

	}
	// �I��
	void end() {

	}
	// ���s����
	bool isRunning() { return (ProcessMessage() == 0 && ClearDrawScreen() == 0 && Keyboard::GetInstance().KeyStateUp(KEYCODE::ESC)); }

	void etceteraUpdate() {
		//deltaTime�̍X�V
		Time::GetInstance().update();
		//���͂̍X�V
		InputChecker::GetInstance().Update();
		//DualShock4��p�̓��͍X�V
		DualShock4Manager::GetInstance().Update();
		EffekseerManager::GetInstance().Update();

	}
	// �R�s�[�֎~
	MyGame(const MyGame& other) = delete;
	MyGame& operator = (const MyGame& other) = delete;

private:
	// �E�B���h�E�̕�
	int mWidth;
	// �E�B���h�E�̍���
	int mHeight;
	// �E�C���h�E�̕`��䗦
	float mRate;
	// �E�C���h�E���[�h���H
	int mWindow;
	// FPS
	float mFps;
	//�V�[���Ǘ��N���X
	SceneManager sceneManager_;
};