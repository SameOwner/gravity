#include "CameraWind.h"
#include"../../Define.h"
#include"../../Math/Random.h"
#include"../../Math/Matrix2D.h"
#include"../../Math/MathHelper.h"

#include<algorithm>

CameraWind::CameraWind()
{
	stop();
}

CameraWind::~CameraWind()
{
	windPoints_.clear();
}

void CameraWind::initialize()
{
	windPoints_.clear();


	for (int i = 0; i < WindSize; i++) {
		create();
		//float angle = Random::GetInstance().Range(0.0f, 360.0f);
		//Vector2 position = center + baseVector*Matrix2D::createAngle(angle);
		//windPoints_.push_back(std::make_pair(position, 0.0f));

	}
}

void CameraWind::stop()
{
	windPoints_.clear();
}

void CameraWind::update(float deltaTime)
{
	for (auto& w : windPoints_) {
		std::get<1>(w) += deltaTime*4.0f;
	}
	windPoints_.remove_if([](std::tuple<Vector2, float,float,float>& pr) {return std::get<1>(pr) >= 1.0f; });

	int createCount = WindSize - windPoints_.size();
	for (int i = 0; i < createCount; i++) {
		create();
	}
}

void CameraWind::draw()const
{
	if (windPoints_.empty())return;

	Vector2 center{ WINDOW_WIDTH*0.5f,WINDOW_HEIGHT*0.5f };
	Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_WINDEFFECT);
	for (auto& w : windPoints_) {
		float alpha = (MathHelper::Sin(std::get<1>(w)) + 1.0f)*0.5f;
		Vector2 drawPos = Vector2::Lerp(std::get<0>(w), (std::get<0>(w) - center)*std::get<3>(w) + center, std::get<1>(w));
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_WINDEFFECT, drawPos, origin, alpha	, Vector2::One*0.4f, std::get<2>(w));
		//DrawCircle(drawPos.x,drawPos.y, 16, GetColor(255, 255, 255));
	}
}

void CameraWind::create()
{
	Vector2 center{ WINDOW_WIDTH*0.5f, WINDOW_HEIGHT*0.5f };//中心
	Vector2 baseVector{ Vector2::Right*350.0f };//回転基準ベクトル
	
	float angle = Random::GetInstance().Range(0.0f, 360.0f);
	Vector2 position = center + baseVector*Matrix2D::createAngle(angle);
	windPoints_.push_back(std::make_tuple(position, Random::GetInstance().Range(0.0f, 0.5f), -angle, Random::GetInstance().Range(3.0f, 5.0f)));

}
