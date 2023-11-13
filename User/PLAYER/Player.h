/**
 * @file Player.h
 * @brief プレイヤー本体
 */

#pragma once
#include "Input.h"
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"Audio.h"

#include"PlayerHp.h"
#include"PlayerState.h"
#include"PlayerUI.h"

#include "Object3d.h"

class Player {
public:
	//アニメーション番号
	enum Animation {
		JUMP,//0
		JUMPATTACK,//1
		DASH,//2
		AVOID,//3
		ATTACK,//4
		STAND,//5
	};

	//攻撃力
	enum Power {
		ZERO = 0,
		ATTACK_POWER = 10,
		JUMPATTACK_POWER = 20,
	};

public:
	//設定
	Player();
	~Player();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief カメラセット
	*/
	void SetCamera(Camera* camera) { camera_ = camera; };

	/**
	 * @brief 更新
	*/
	void Update();

	/**
	 * @brief カメラ回転
	*/
	void CamRota();

	/**
	 * @brief 描画
	*/
	void Draw();

	/**
	 * @brief スプライト描画
	*/
	void DrawSprite();

	/**
	 * @brief 状態移行
	*/
	void TransitionTo(PlayerState* state);

	/**
	 * @brief サウンド再生
	*/
	void PlayWav(const std::string& filename);

	/**
	 * @brief サウンド停止
	*/
	void StopWav();

	/**
	 * @brief アニメーション切り替え
	*/
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	/**
	 * @brief 移動
	*/
	void Move(Vector3 velocity);

	/**
	 * @brief y座標セット
	*/
	void SetPosY(float posY) { fbxObject3d_->wtf.position.y = posY; };

	/**
	 * @brief y座標セット
	*/
	void SetInvincible(bool isInvincible) { isInvincible_ = isInvincible; };

	/**
	 * @brief y軸回転セット
	*/
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };

	/**
	 * @brief 座標取得
	*/
	Transform GetWtf() { return fbxObject3d_->wtf; };

	/**
	 * @brief 座標ポインタ取得
	*/
	Transform* GetWtfP() { return &fbxObject3d_->wtf; };

	/**
	 * @brief カメラ座標取得
	*/
	Transform GetCamWtf() { return camera_->wtf; };

	/**
	 * @brief 剣座標取得
	*/
	Vector3 GetSwordPos() { return fbxObject3d_->GetBonWorldPos(boneNum[4]); };

	/**
	 * @brief 被ダメ処理
	*/
	void OnCollision();

	/**
	 * @brief 生存フラグ
	*/
	bool IsLive() { return hp_->IsLive(); };

	/**
	 * @brief 現在の体力取得
	*/
	int GetHp() { return hp_->GetHp(); };
	/**
	 * @brief 受けているダメージ量取得
	*/
	int GetDamage() { return damageGauge_; };
	/**
	 * @brief 攻撃状態か取得
	*/
	bool GetIsAttack() { return state_->GetIsAttack(); };
	/**
	 * @brief 攻撃力取得
	*/
	int GetPower() { return state_->GetPower(); };
	/**
	 * @brief 押し出し時半径取得
	*/
	float GetRad() { return rad_; };


private:
	//カメラ
	Camera* camera_ = nullptr;
	//入力
	Input* input_ = nullptr;
	//サウンド
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice_[10] = { 0 };

	//体力
	PlayerHp* hp_ = nullptr;

	//当たり判定
	const float rad_ = 0.4f;
	const int maxColliderNum = 5;
	BaseCollider* colliders_[5];
	uint32_t boneNum[5];

	bool isInvincible_;

	//HPゲージ管理
	int gaugeTimer_;
	int gaugeLimit_;
	int damageGauge_;

	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//UI
	PlayerUI ui_;

	//行動
	PlayerState* state_ = nullptr;
};