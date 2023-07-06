#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"

#include"Action.h"

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();
	void SetPlayerTransform(Transform* playerWtf);

	void Update();

	void Draw();

private:
	//モデル
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//行動
	Action* action = nullptr;
};