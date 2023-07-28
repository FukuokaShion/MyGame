#pragma once
#include "Input.h"
#include "FBXModel.h"
#include "FBXObject3d.h"
#include"CollisionPrimitive.h"

#include"PlayerHp.h"
#include"PlayerState.h"

class Player {
public:
	Player();
	~Player();
	void Initialize(Input* input);
	void SetCamera(Camera* camera) { camera_ = camera; };

	void Update();
	void OnCollision(int damage);
	void Move(Vector3 velocity) { fbxObject3d_->wtf.position += velocity; };
	void Draw();

	Transform* GetWtf() { return &fbxObject3d_->wtf; };
	bool IsLive() { return hp->IsLive(); };

	bool GetIsAttack() { return state_->GetIsAttack(); };
	int GetPower() { return state_->GetPower(); };

	void TransitionTo(PlayerState* state);

	void Move();
	void Rota();
	void CamRota();


public:
	//カメラ
	Camera* camera_ = nullptr;

	//体当たり判定
	Cylinder bodyHitBox;

	//攻撃当たり判定
	Sphere attackHitBox;

	//モデル
	FBXObject3d* fbxObject3d_ = nullptr;

	///ステータス
	PlayerHp* hp = nullptr;

	//入力
	Input* input_ = nullptr;
private:
	//モデル
	FBXModel* fbxModel_ = nullptr;

	//行動
	PlayerState* state_ = nullptr;

};