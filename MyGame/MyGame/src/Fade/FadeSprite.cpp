#include "FadeSprite.h"
#include"../Math/Vector2.h"
#include"../Graphic/Sprite.h"
#include"../Math/Easing.h"
#include"../Define.h"

static const float fadeSpeed = 5.0f;

FadeSprite::FadeSprite():isActive_{false},state_{Out}
{
}

FadeSprite::~FadeSprite()
{
}

void FadeSprite::init()
{
	isActive_ = false;
	state_ = Out;
	fadeTimer_ = 0.0f;
	timer_ = 0.0f;
	function_ = []() {};
}

void FadeSprite::start()
{
	fadeTimer_ = 0.0f;
	isActive_ = true;
	state_ = Out;
	timer_ = 0.0f;
}

void FadeSprite::update(float deltaTime)
{
	if (!isActive_)return;

	switch (state_)
	{
	case In:
		in(deltaTime);
		break;
	case Out:
		out(deltaTime);
		break;
	case Stop:
		stop(deltaTime);
		break;
	default:
		break;
	}


}

void FadeSprite::draw() const
{
	if (!isActive_)return;
	auto size = Sprite::GetInstance().GetSize(SPRITE_ID::FADE_SPRITE);

	float fade = Easing::EaseOutQuad(fadeTimer_, 0.0f, size.x*0.6f, 1.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::FADE_SPRITE, Vector2{ -size.x + fade,0.0f });
	Sprite::GetInstance().Draw(SPRITE_ID::FADE_SPRITE, Vector2{ WINDOW_WIDTH - fade,0.0f });

}

bool FadeSprite::isActive() const
{
	return isActive_;
}

void FadeSprite::addCallBack(const std::function<void()>& func)
{
	function_ = func;
}

void FadeSprite::in(float deltaTime)
{
	fadeTimer_ -= deltaTime*fadeSpeed;
	if (fadeTimer_ <= 0.0f) {
		fadeTimer_ = 0.0f;
		isActive_ = false;
	}
}

void FadeSprite::stop(float deltaTime)
{
	timer_ += deltaTime*fadeSpeed;
	if (timer_ > 1.0f) {
		state_ = In;
	}
}

void FadeSprite::out(float deltaTime)
{
	fadeTimer_ += deltaTime*fadeSpeed;

	if (fadeTimer_ >= 1.0f) {
		state_ = Stop;
		function_();
	}
}
