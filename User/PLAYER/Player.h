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

#include "Object3d.h"

class Player {
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
	BaseCollider* body_;
	BaseCollider* body2_;
	BaseCollider* body3_;
	BaseCollider* body4_;
	BaseCollider* body5_;
	uint32_t num[4];

	//HPゲージ管理
	int gaugeTimer_;
	int gaugeLimit_;
	int damageGauge_;

	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//行動
	PlayerState* state_ = nullptr;
};