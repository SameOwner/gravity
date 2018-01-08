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
		// 前アニメーションをデタッチ
		MV1DetachAnim(model_, currentAnim_);
		MV1DetachAnim(model_, previousAnim_);
	}

	//frameTime=フレーム変更割合
	void update(float frameTime) {


		// 前アニメーションをデタッチ
		MV1DetachAnim(model_, currentAnim_);
		MV1DetachAnim(model_, previousAnim_);

		// 今アニメーションをアタッチ
		currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
		currentAnimTime_ += frameTime*animSpeed_;
		if (currentAnimTime_ >= maxAnimTime_)
		{
			isEnd_ = true;
			if (isLoop_) currentAnimTime_ = fmodf(currentAnimTime_, maxAnimTime_);
			else currentAnimTime_ = maxAnimTime_;
		}

		// 前アニメーションをアタッチ
		previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

		//前アニメーションがループ対応だったら
		if (prevIsLoop_) {
			// 前アニメーション更新
			float prevMaxAnimTime = MV1GetAttachAnimTotalTime(model_, previousAnim_);
			previousAnimTime_ += frameTime*animSpeed_;
			previousAnimTime_ = fmodf(previousAnimTime_, prevMaxAnimTime);
		}
		// ブレンド率の更新
		blendRate_ += RATE_TIME;
		blendRate_ = max(0.0f, min(blendRate_, 1.0f));
	}
	void Draw(const Matrix& rotation) const
	{
		// アニメーションのブレンド
		MV1SetAttachAnimBlendRate(model_, previousAnim_, 1.0f - blendRate_);
		MV1SetAttachAnimBlendRate(model_, currentAnim_, blendRate_);
		// 描画
		MV1SetAttachAnimTime(model_, previousAnim_, previousAnimTime_);
		MV1SetAttachAnimTime(model_, currentAnim_, currentAnimTime_);

		Model::GetInstance().Draw(model_, rotation);
	}

	void changeAnimation(int key,bool isLoop=true,float animSpeed=1.0f,float blendRate=1.0f,float animTime=0.0f) {
		//アニメーションが前と一緒なら変更しない
		if (currentAnimKey_ == key)return;

		// 前アニメーションをデタッチ
		MV1DetachAnim(model_, currentAnim_);
		MV1DetachAnim(model_, previousAnim_);

		//アニメーションキー番号をセット
		previousAnimKey_ = currentAnimKey_;
		currentAnimKey_ = key;
	
		//アニメーションをセット
		currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
		previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

		//再生位置を設定
		previousAnimTime_ = currentAnimTime_;
		currentAnimTime_ = animTime;

		//アニメーション最大時間の更新
		maxAnimTime_ = MV1GetAttachAnimTotalTime(model_, currentAnim_);

		prevIsLoop_ = isLoop_;
		isLoop_ = isLoop;
		isEnd_ = false;
		blendRate_ = 1.0f - blendRate;//ブレンド比率分前アニメーションをブレンドする
		animSpeed_ = animSpeed;
	}

	bool isEnd()const { return isEnd_; }
private:
	int model_;//モデルハンドル
	
	int currentAnimKey_{ -1 };//現アニメーションキー
	int previousAnimKey_{ -1 };//前アニメーションキー

	int currentAnim_{ -1 };//現アニメーション
	int previousAnim_{ -1 };//前アニメーション
	
	float currentAnimTime_{ 0.0f };//現アニメーション再生位置
	float previousAnimTime_{ 0.0f };//前アニメーション再生位置

	float blendRate_{ 0.0f };//ブレンド比率
	float animSpeed_{ 0.0f };//アニメーション再生倍率

	float maxAnimTime_{ 0.0f };//アニメーション最大時間

	bool isLoop_{ true };//ループするか
	bool prevIsLoop_{ true };//前アニメーションがループするか

	bool isEnd_{ false };//終わったか
private:
	const float RATE_TIME = 0.1f;// ブレンドレートタイム

};