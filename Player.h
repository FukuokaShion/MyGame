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
	//���f��
	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;


};