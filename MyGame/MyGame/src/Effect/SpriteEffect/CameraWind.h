#pragma once
#include"../../Graphic/Sprite.h"
#include<list>
#include"../../Math/Vector2.h"

class CameraWind {
public:
	CameraWind();
	~CameraWind();

	void initialize();
	void stop();
	void update(float deltaTime);

	void draw()const;

	void create();
private:
	//風エフェクトの数
	int WindSize{ 40 };
	//風群の管理(ポジション,割合,角度,速度)
	std::list<std::tuple<Vector2, float,float,float>> windPoints_;
};