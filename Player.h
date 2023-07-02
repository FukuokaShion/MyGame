#pragma once

#include "FBXModel.h"
#include "FBXObject3d.h"


class Player {
public:
	Player();

	~Player();

	void Update();

	void Draw();

private:
	//ƒ‚ƒfƒ‹
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;


};