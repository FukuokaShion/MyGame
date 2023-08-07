#include "Easing.h"

Vector3 Easing::InQuadVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = powf(time, 2);
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::OutQuadVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t = (1 - powf(1 - time, 2));
	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}

Vector3 Easing::InOutQuadVec3(const Vector3& start, const Vector3& end, const float time)
{
	float t;
	if (time < 0.5f)
	{
		t = 2 * powf(time, 2);
	}
	else
	{
		t = (1 - powf(-2 * time + 2, 2) / 2);
	}

	Vector3 A, B;
	A = Vector3(start.x * (1.0f - t), start.y * (1.0f - t), start.z * (1.0f - t));
	B = Vector3(end.x * t, end.y * t, end.z * t);

	Vector3 position;
	position = Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
	return position;
}