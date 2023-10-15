/**
 * @file Field.h
 * @brief ゲームシーンのステージ
 */

#pragma once
#include "Object3d.h"

class Field {
public:
	Field();
	~Field();

	void Initialize();

	void Update();

	void Draw();
private:
	//背景や床
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;

	Object3d* floor = nullptr;
	Model* floorMD = nullptr;
	Object3d* water = nullptr;
	Model* waterMD = nullptr;

	Object3d* rock01[3];
	Model* rock01MD = nullptr;
	Object3d* rock02[3];
	Model* rock02MD = nullptr;

};