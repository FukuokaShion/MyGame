/**
 * @file Enemy.h
 * @brief　敵クラス本体
 */

#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"
#include"EnemyDeathParticle.h"
#include"Audio.h"

#include"EnemyHp.h"
#include"EnemyState.h"
#include"EnemyBullet.h"
#include"EnemyUI.h"

class Enemy {
public:
	enum Animation {
		SHAKE,//0
		STAND,//1
	};

public:
	Enemy();
	~Enemy();
	
	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update(Vector3 playerPos);

	/**
	 * @brief FBX描画
	*/
	void Draw();

	/**
	 * @brief Obj描画
	*/
	void ObjDraw();

	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw();

	/**
	 * @brief 状態移行
	*/
	void TransitionTo(EnemyState* state);

	/**
	 * @brief サウンド再生
	*/
	void PlayWave(const std::string& filename);

	/**
	 * @brief アニメーション切り替え
	*/
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	/**
	 * @brief 座標移動
	*/
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	
	/**
	 * @brief Y軸回転
	*/
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };
	
	/**
	 * @brief 座標取得
	*/
	Transform GetWtf() { return fbxObject3d_->wtf; };

	/**
	 * @brief 被ダメ処理
	*/
	void OnCollision();

	/**
	 * @brief 生存フラグ
	 */
	bool IsLive() { return hp_->IsLive(); };

	/**
	 * @brief ゲッター
	 */
	int GetHp() { return hp_->GetHp(); };
	bool GetIsAttack() { return isAttack_; };
	int GetPower() { return power_; };


	/**
	 * @brief 押し出し時半径取得
	*/
	float GetRad() { return rad_; };

	/**
	 * @brief セッター
	 */
	void SetIsAttack(bool isAttack) { this->isAttack_ = isAttack; };
	void setPower(int power) { this->power_ = power; };

	/**
	 * @brief弾生成
	 */
	void CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);

private:
	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_[10] = { 0 };

	//行動
	EnemyState* state_ = nullptr;

	//体力
	EnemyHp* hp_ = nullptr;

	//当たり判定
	const float rad_ = 1.3f;
	const int MaxColliderNum = 5;
	BaseCollider* colliders_[5];
	uint32_t boneNum_[5];

	//UI
	EnemyUI ui_;

	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//弾リスト
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	//攻撃判定
	bool isAttack_;
	int power_;

	//パーティクル
	EnemyParticle* particle_ = nullptr;

	//死亡時
	const int DeathLimit = 210;
	int DeathTimer;
	EnemyDeathParticle* deatgparticle_ = nullptr;

};