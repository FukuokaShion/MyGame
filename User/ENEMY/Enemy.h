#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"
#include"EnemyParticle.h"
#include"Audio.h"

#include"EnemyHp.h"
#include"EnemyState.h"
#include"EnemyBullet.h"

class Enemy {
public:
	//設定
	Enemy();
	~Enemy();
	void Initialize();

	//更新
	void Update(Vector3 playerPos);

	//描画
	void Draw();
	void ObjDraw();

	//状態以降
	void TransitionTo(EnemyState* state);

	//サウンド
	void PlayWave(const std::string& filename);

	//アニメーション切り替え
	void AnimationChange(int animationNum = 0, float speed = 1.0f) { fbxObject3d_->PlayAnimation(animationNum, speed); };

	//座標
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	void RotaY(float theta) { fbxObject3d_->wtf.rotation.y = theta; };
	Transform GetWtf() { return fbxObject3d_->wtf; };

	//被ダメ処理
	void OnCollision();

	//ステータス
	bool IsLive() { return hp->IsLive(); };
	int GetHp() { return hp->GetHp(); };
	bool GetIsAttack() { return isAttack_; };
	int GetPower() { return power_; };
	void SetIsAttack(bool isAttack) { this->isAttack_ = isAttack; };
	void setPower(int power) { this->power_ = power; };

	//弾生成
	void CreatBullet(Vector3 pos, Vector3 velocity, int liveLimit, int stayTime = 0);

private:
	//サウンド
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	//行動
	EnemyState* state_ = nullptr;

	//体力
	EnemyHp* hp = nullptr;

	//当たり判定
	BaseCollider* body;

	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//弾リスト
	std::list<std::unique_ptr<EnemyBullet>> bullets;

	//攻撃判定
	bool isAttack_;
	int power_;

	EnemyParticle* particle = nullptr;

};