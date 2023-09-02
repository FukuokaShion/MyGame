#pragma once
#include "Input.h"
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"Audio.h"

#include"PlayerHp.h"
#include"PlayerState.h"

class Player {
public:
	//設定
	Player();
	~Player();
	void Initialize(Input* input);
	void SetCamera(Camera* camera) { camera_ = camera; };

	//更新
	void Update();
	void CamRota();

	//描画
	void Draw();

	//状態移行
	void TransitionTo(PlayerState* state);

	//サウンド
	void PlayWav(const std::string& filename);
	void StopWav();

	//FBX
	//アニメーション切り替え
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	//座標
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	void SetPosY(float posY) { fbxObject3d_->wtf.position.y = posY; };
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };
	Transform GetWtf() { return fbxObject3d_->wtf; };
	Transform* GetWtfP() { return &fbxObject3d_->wtf; };
	Transform GetCamWtf() { return camera_->wtf; };

	//攻撃当たり判定
	Sphere GetAttackHitBox() { return attackHitBox; };
	void SetAttackRad(float newRad) { attackHitBox.radius = newRad; };
	void SetAttackPos(Vector3 newPos) { attackHitBox.center = newPos; };

	//体当たり判定
	Cylinder GetBodyHitBox() { return bodyHitBox; };

	//被ダメ処理
	void OnCollision(int damage);
	
	//ステータス
	bool IsLive() { return hp->IsLive(); };
	int GetHp() { return hp->GetHp(); };
	int GetDamage() { return damageGauge; };
	bool GetIsAttack() { return state_->GetIsAttack(); };
	int GetPower() { return state_->GetPower(); };


private:
	//カメラ
	Camera* camera_ = nullptr;
	//入力
	Input* input_ = nullptr;
	//サウンド
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice[10] = {0};

	//体力
	PlayerHp* hp = nullptr;

	//攻撃当たり判定
	Sphere attackHitBox;
	//体当たり判定
	Cylinder bodyHitBox;
	//HPゲージ管理
	int gaugeTimer;
	int gaugeLimit;
	int damageGauge;

	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//行動
	PlayerState* state_ = nullptr;
};