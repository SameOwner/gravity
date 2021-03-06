#pragma once

struct Matrix;

class AnimationDx
{
public:
	// コンストラクタ
	explicit AnimationDx() = default;
	// デストラクタ
	~AnimationDx();
	// 更新
	void Update(const float frameTime);
	// 描画
	void Draw(const Matrix& rotation) const;
	// アニメーション切り替え
	void ChangeAnim(const int motion, const float frame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blend = 1.0f, bool forceChange = false);
	// モデルハンドル登録(受け取ったハンドルを基にモデルをコピーするため、受取時のハンドルをそのまま使う事は出来ない)
	void SetHandle(const int& handle);
	// アニメーションエンドフラグ
	bool IsAnimEnd() const;
	// 今のアニメーションフレームを受け取る
	float GetCurrentAnimFrame() const;
	// モーションの最終フレームを受け取る
	float GetEndAnimFrame(const int motion) const;
	//現アニメーションの終了時間を受け取る
	float GetAnimMaxTime()const;
	//指定アニメーションの終了時間を受け取る
	float GetAnimMaxTime(int index)const;
	//ループするかの設定
	void setLoop(bool isLoop) { isLoop_ = isLoop; }
	//アニメーションの再生速度を設定する
	void setAnimSpeed(float animSpeed) { animSpeed_ = animSpeed; }
	//モデルハンドルの取得
	int getModelHandle() const;
	void lastAnim();
private:
	void clearModel();
	// コピーコンストラクタ
	AnimationDx(const AnimationDx& other) = delete;
	// 代入演算子
	AnimationDx& operator =(const AnimationDx& other) = delete;

private:
	// ブレンドレートタイム
	const float RATE_TIME = 0.1f;
	// モデルハンドル
	int		modelHandle_{ -1 };
	// 今モーション
	int		motion_;
	// 前モーション
	int		prevMotion_;
	// アニメーションタイマー
	float	animTimer_;
	// 前アニメーションタイマー
	float	prevAnimTimer_;
	// アニメーションマックスタイム
	float	maxAnimTime_;
	// アニメーション終了フラグ
	bool	isAnimEnd_;
	// ブレンドレート
	float	rate_;
	// 今アニメーション
	int		anim_;
	// 前アニメーション
	int		prevAnim_;
	//ループするか
	bool isLoop_{ true };
	//前のアニメーションがループしていたか
	bool prevLoop_{ true };
	//アニメーションの再生速度
	float animSpeed_{ 1.0f };
};
