/**
 * @file Quaternion.h
 * @brief Quaternion
 */

#pragma once
#include"vector3.h"
#include"Matrix4.h"

namespace MyEngine {
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Quaternion();
		Quaternion(float x, float y, float z, float w);

		/**
		 * @brief 積を計算
		*/
		Quaternion Multiply(Quaternion quaternion);

		/**
		 * @brief 単位Quaternionを返す
		*/
		Quaternion IdentityQuaternion();

		/**
		 * @brief 共役Quaternionを返す
		*/
		Quaternion Conjugate();

		/**
		 * @brief ノルム
		*/
		float Norm() const;

		/**
		 * @brief 正規化
		*/
		Quaternion Normalize();

		/**
		 * @brief 逆Quaternionを返す
		*/
		Quaternion Inverse();

		/**
		 * @brief クトルをQuaternionで回転
		*/
		Vector3 RotateVector(const Vector3& vector);

		/**
		 * @brief 回転行列計算
		*/
		Matrix4 MakeRotateMatrix();

		//単項演算子オーバーロード
		Quaternion operator+() const;
		Quaternion operator-() const;

		//代入演算子オーバーロード
		Quaternion& operator+=(const Quaternion& v);
		Quaternion& operator-=(const Quaternion& v);
		Quaternion& operator*=(float s);
		Quaternion& operator/=(float s);


	};

	Vector3 MatVector(const Vector3& vector, const Matrix4& matrix);

	//任意軸回転を表すQuaternionの生成
	Quaternion MakeAxisAngle(const Vector3& axis, float radian);

	//
	Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);


	//2項演算子オーバーロード
	//いろんな引数(引数の型と順序)のパターンに対応するため、以下のように準備している
	const Quaternion operator+(const Quaternion& v1, const Quaternion& v2);
	const Quaternion operator-(const Quaternion& v1, const Quaternion& v2);
	const Quaternion operator*(const Quaternion& v, float s);
	const Quaternion operator*(float s, const Quaternion& v);

	const Quaternion operator/(const Quaternion& v, float s);
}