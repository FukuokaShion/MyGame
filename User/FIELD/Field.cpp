/**
 * @file Field.cpp
 * @brief ゲームシーンのステージ描画
 */

#include"Field.h"

Field::Field() {

}

void Field::Initialize() {
	//背景
	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	floorMD = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorMD);

	waterMD = Model::LoadFromOBJ("water");
	water = Object3d::Create();
	water->SetModel(waterMD);
	water->wtf.scale = { 2,1,2 };

	rock01MD = Model::LoadFromOBJ("rock01");
	rock02MD = Model::LoadFromOBJ("rock02");

	for (int i = 0; i < 3; i++) {
		rock01[i] = Object3d::Create();
		rock01[i]->SetModel(rock01MD);
		rock02[i] = Object3d::Create();
		rock02[i]->SetModel(rock02MD);
	}

	float PI = 3.141592f;

	rock01[0]->wtf.position = { 42,0,65 };
	rock01[0]->wtf.scale = { 5,5,5 };
	rock01[0]->wtf.rotation = { 0,0,0 };

	rock01[1]->wtf.position = { 122,0,10 };
	rock01[1]->wtf.scale = { 5,5,5 };
	rock01[1]->wtf.rotation = { PI / 4,0,0 };

	rock01[2]->wtf.position = { -26,0,-73 };
	rock01[2]->wtf.scale = { 5,5,5 };
	rock01[2]->wtf.rotation = { 0,0,0 };

	rock02[0]->wtf.position = { -45,0,105 };
	rock02[0]->wtf.scale = { 12,12,12 };
	rock02[0]->wtf.rotation = { 0,0,0 };

	rock02[1]->wtf.position = { 75,0,-75 };
	rock02[1]->wtf.scale = { 10,10,10 };
	rock02[1]->wtf.rotation = { 0,-3.0f * PI / 4.0f,0 };

	rock02[2]->wtf.position = { -91,0,-49 };
	rock02[2]->wtf.scale = { 8,8,8 };
	rock02[2]->wtf.rotation = { 0,3.0f * PI / 20.0f,0 };
}

Field::~Field() {
	delete skydome;
	delete skydomeMD;

	delete floor;
	delete floorMD;
	delete water;
	delete waterMD;

	for (int i = 0; i < 3; i++) {
		delete rock01[i];
		delete rock02[i];
	}

	delete rock01MD;
	delete rock02MD;
}

void Field::Update() {
	skydome->Update();
	floor->Update();
	water->Update();
	for (int i = 0; i < 3; i++) {
		rock01[i]->Update();
		rock02[i]->Update();
	}
}

void Field::Draw() {
	skydome->Draw();

	floor->Draw();
	water->Draw();

	for (int i = 0; i < 3; i++) {
		rock01[i]->Draw();
		rock02[i]->Draw();
	}
}