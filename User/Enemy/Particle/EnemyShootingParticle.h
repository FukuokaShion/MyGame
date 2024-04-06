/**
 * @file EnemyShootingParticle.h
 * @brief 弾生成時パーティクル
 */

#pragma once
#include "ParticleManager.h"

using namespace MyEngine;

class EnemyShootingParticle {
public:
	EnemyShootingParticle();
	~EnemyShootingParticle();

	/**
	 * @brief 発生
	*/
	void Create(Vector3 createPos);

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief 描画
	*/
	void Draw();

public:
	//パーティクル
	std::unique_ptr<ParticleManager> shootingParticle_;
};