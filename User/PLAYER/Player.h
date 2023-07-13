#pragma once
#include "Input.h"
#include "FBXModel.h"
#include "FBXObject3d.h"

#include"PlayerHp.h"
#include"PlayerAction.h"

class Player {
public:
	Player();
	~Player();
	void Initialize(Input* input);
	void SetCamera(Camera* camera) { camera_ = camera; };

	void Update();
	void OnCollision(int damage);
	void Draw();

	Transform* GetWtf() { return &fbxObject3d_->wtf; };
	bool IsLive() { return hp->IsLive(); };

	bool GetIsAttack() { return action->GetIsAttack(); };
	int GetPower() { return action->GetPower(); };

private:
	void Move();
	void Rota();
	void CamRota();

private:
	//入力
	Input* input_ = nullptr;
	//カメラ
	Camera* camera_ = nullptr;

	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//行動
	PlayerAction* action = nullptr;

	///ステータス
	PlayerHp* hp = nullptr;
};