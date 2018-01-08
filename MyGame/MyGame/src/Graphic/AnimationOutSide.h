#pragma once
#include"AnimLoader.h"
#include"../ID/EnumIDs.h"
#include"../Math/Matrix.h"
#include"../Graphic/Model.h"

class AnimationOutSide {
public:

	explicit AnimationOutSide(int model): model_{ model } {

	}
	~AnimationOutSide() {
		// �O�A�j���[�V�������f�^�b�`
		MV1DetachAnim(model_, currentAnim_);
		MV1DetachAnim(model_, previousAnim_);
	}

	//frameTime=�t���[���ύX����
	void update(float frameTime) {


		// �O�A�j���[�V�������f�^�b�`
		MV1DetachAnim(model_, currentAnim_);
		MV1DetachAnim(model_, previousAnim_);

		// ���A�j���[�V�������A�^�b�`
		currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
		currentAnimTime_ += frameTime*animSpeed_;
		if (currentAnimTime_ >= maxAnimTime_)
		{
			isEnd_ = true;
			if (isLoop_) currentAnimTime_ = fmodf(currentAnimTime_, maxAnimTime_);
			else currentAnimTime_ = maxAnimTime_;
		}

		// �O�A�j���[�V�������A�^�b�`
		previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

		//�O�A�j���[�V���������[�v�Ή���������
		if (prevIsLoop_) {
			// �O�A�j���[�V�����X�V
			float prevMaxAnimTime = MV1GetAttachAnimTotalTime(model_, previousAnim_);
			previousAnimTime_ += frameTime*animSpeed_;
			previousAnimTime_ = fmodf(previousAnimTime_, prevMaxAnimTime);
		}
		// �u�����h���̍X�V
		blendRate_ += RATE_TIME;
		blendRate_ = max(0.0f, min(blendRate_, 1.0f));
	}
	void Draw(const Matrix& rotation) const
	{
		// �A�j���[�V�����̃u�����h
		MV1SetAttachAnimBlendRate(model_, previousAnim_, 1.0f - blendRate_);
		MV1SetAttachAnimBlendRate(model_, currentAnim_, blendRate_);
		// �`��
		MV1SetAttachAnimTime(model_, previousAnim_, previousAnimTime_);
		MV1SetAttachAnimTime(model_, currentAnim_, currentAnimTime_);

		Model::GetInstance().Draw(model_, rotation);
	}

	void changeAnimation(int key,bool isLoop=true,float animSpeed=1.0f,float blendRate=1.0f,float animTime=0.0f) {
		//�A�j���[�V�������O�ƈꏏ�Ȃ�ύX���Ȃ�
		if (currentAnimKey_ == key)return;

		// �O�A�j���[�V�������f�^�b�`
		MV1DetachAnim(model_, currentAnim_);
		MV1DetachAnim(model_, previousAnim_);

		//�A�j���[�V�����L�[�ԍ����Z�b�g
		previousAnimKey_ = currentAnimKey_;
		currentAnimKey_ = key;
	
		//�A�j���[�V�������Z�b�g
		currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
		previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

		//�Đ��ʒu��ݒ�
		previousAnimTime_ = currentAnimTime_;
		currentAnimTime_ = animTime;

		//�A�j���[�V�����ő厞�Ԃ̍X�V
		maxAnimTime_ = MV1GetAttachAnimTotalTime(model_, currentAnim_);

		prevIsLoop_ = isLoop_;
		isLoop_ = isLoop;
		isEnd_ = false;
		blendRate_ = 1.0f - blendRate;//�u�����h�䗦���O�A�j���[�V�������u�����h����
		animSpeed_ = animSpeed;
	}

	bool isEnd()const { return isEnd_; }
private:
	int model_;//���f���n���h��
	
	int currentAnimKey_{ -1 };//���A�j���[�V�����L�[
	int previousAnimKey_{ -1 };//�O�A�j���[�V�����L�[

	int currentAnim_{ -1 };//���A�j���[�V����
	int previousAnim_{ -1 };//�O�A�j���[�V����
	
	float currentAnimTime_{ 0.0f };//���A�j���[�V�����Đ��ʒu
	float previousAnimTime_{ 0.0f };//�O�A�j���[�V�����Đ��ʒu

	float blendRate_{ 0.0f };//�u�����h�䗦
	float animSpeed_{ 0.0f };//�A�j���[�V�����Đ��{��

	float maxAnimTime_{ 0.0f };//�A�j���[�V�����ő厞��

	bool isLoop_{ true };//���[�v���邩
	bool prevIsLoop_{ true };//�O�A�j���[�V���������[�v���邩

	bool isEnd_{ false };//�I�������
private:
	const float RATE_TIME = 0.1f;// �u�����h���[�g�^�C��

};