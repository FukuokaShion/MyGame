#pragma once
#include "Vector3.h"
#include <math.h>

class Easing {
public:
	static Vector3 InQuadVec3(const Vector3& start, const Vector3& end, const float time);
	static Vector3 OutQuadVec3(const Vector3& start, const Vector3& end, const float time);
	static Vector3 InOutQuadVec3(const Vector3& start, const Vector3& end, const float time);

};