/**
 * @file GameCamera.h
 * @brief ゲームカメラ
 */

#pragma once
#include"Camera.h"
#include "Vector2.h"
#include"Input.h"

class GameCamera : public Camera {
public:
	/**
	 * @brief 初期化
	*/
	GameCamera();
	void Initialize(int window_width, int window_height) override;

	/**
	 * @brief 更新
	*/
	void Update() override;


	/**
	 * @brief 感度セット
	*/
	void SetSensitivity(Vector2 sensitivity) { sensitivity_ = sensitivity; };
	/**
	 * @brief 親座標セット
	*/
	void SetParentPos(Vector3 parentPos) { parentPos_ = parentPos; };
	/**
	 * @brief 親視線ベクトルセット
	*/
	void SetParentViewVec(Vector3 SetParentViewVec);

private:
	/**
	 * @brief 回転
	*/
	void Rota();
	/**
	 * @brief 親の視線になる
	*/
	void ViewReset();

private:
	Vector3 parentPos_;
	Vector3 localPos_;

	Vector3 rota_;
	float upLimit_;
	float downLimit_;

	Vector2 sensitivity_;

	Vector3 parentViewVec_;
	Vector3 resetVec;
	bool isViewReset;
	float resetSpeed;
};