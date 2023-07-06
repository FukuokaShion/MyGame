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
	//�w�i�⏰
	Object3d* floor = nullptr;
	Model* floorMD = nullptr;
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;

};