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
	//���G�t�F�N�g�̐�
	int WindSize{ 40 };
	//���Q�̊Ǘ�(�|�W�V����,����,�p�x,���x)
	std::list<std::tuple<Vector2, float,float,float>> windPoints_;
};