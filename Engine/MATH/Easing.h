/**
 * @file Easing.h
 * @brief イージング関数
 */

#pragma once
#include "Vector3.h"
#include <math.h>

class Easing {
public:
	static float InQuad(const float& start, const float& end, const float time);
	static float OutQuad(const float& start, const float& end, const float time);
	static float InOutQuad(const float& start, const float& end, const float time);

	static Vector3 InQuadVec3(const Vector3& start, const Vector3& end, const float time);
	static Vector3 OutQuadVec3(const Vector3& start, const Vector3& end, const float time);
	static Vector3 InOutQuadVec3(const Vector3& start, const Vector3& end, const float time);
};