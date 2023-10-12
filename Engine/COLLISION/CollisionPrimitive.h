#pragma once
#include"Vector3.h"
#include<DirectXMath.h>
#include"CollisionAttribute.h"

class BaseCollider {
public:
	//セッター
	void SetCenter(Vector3 center) { center_ = center; };
	void SetRad(float rad) { radius_ = rad; };
	void SetAttribute(Attribute attribute) { attribute_ = attribute; };
	void IsHit(Attribute attribute, Vector3 hitPos);

	//ゲッター
	Vector3 GetCenter() { return center_; };
	float GetRad() { return radius_; };
	Attribute GetAttribute() { return attribute_; };
	HitTarget GetIsHit() { return isHit_; };
	HitPos GetHitPos() { return hitPos_; };

protected:
	Vector3 center_ = { 0,0,0 };
	float radius_ = 1.0f;
	Attribute attribute_;
	HitTarget isHit_;
	HitPos hitPos_;
};

struct Sphere {
	Vector3 center = { 0,0,0 };
	float radius = 1.0f;

	Attribute attribute;
	HitTarget isHit;
};

struct Cylinder {
	Vector3 center = { 0,0,0 };
	float radius = 1.0f;
	float height = 1.0f;
};

struct Plane {
	Vector3 normal = { 0,1,0 };

	float distance = 0.0f;

};

class Triangle {
public:
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;

	Vector3 normal;

	void ComputeNormal();
};

struct Ray
{
	Vector3 start = { 0,0,0 };

	Vector3 dir = { 1,0,0 };

};

class CollisionPrimitive
{

};