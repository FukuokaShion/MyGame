#pragma once
#include "FBXModel.h"
#include "FBXObject3d.h"

#include"Action.h"

class Enemy {
public:
	Enemy();
	~Enemy();

	void Initialize();

	void Update();

	void Draw();

private:
	//ÉÇÉfÉã
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	//çsìÆ
	Action* action = nullptr;
};