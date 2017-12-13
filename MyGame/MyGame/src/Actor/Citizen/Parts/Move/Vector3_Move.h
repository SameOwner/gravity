#pragma once
#include"../../../../Math/Vector3.h"


class Vector3_Move {
public:
	virtual ~Vector3_Move(){}

	virtual Vector3 operator ()(const Vector3& target) = 0;
};