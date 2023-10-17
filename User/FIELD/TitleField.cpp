/**
 * @file TitleField.cpp
 * @brief ゲームシーンのステージ描画
 */

#include"TitleField.h"

TitleField::TitleField() {

}

void TitleField::Initialize() {
	//obj
	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	waterMD = Model::LoadFromOBJ("water");
	water = Object3d::Create();
	water->SetModel(waterMD);
	water->wtf.scale = { 2,1,2 };

	coastMD = Model::LoadFromOBJ("coast");
	coast = Object3d::Create();
	coast->SetModel(coastMD);
	coast->wtf.scale = { 2,1,2 };
	coast->wtf.rotation.y = 3.14f;

	rock01MD = Model::LoadFromOBJ("rock01");
	rock02MD = Model::LoadFromOBJ("rock02");

	for (int i = 0; i < 2; i++) {
		rock01[i] = Object3d::Create();
		rock01[i]->SetModel(rock01MD);
		rock02[i] = Object3d::Create();
		rock02[i]->SetModel(rock02MD);
	}

	rock01[0]->wtf.position = { -50,0,240 };
	rock01[0]->wtf.scale = { 1.4f,1,1 };
	rock01[0]->wtf.rotation = { 0,0,0 };

	rock01[1]->wtf.position = { -60,0,250 };
	rock01[1]->wtf.scale = { 1,1.3f,1.2f };
	rock01[1]->wtf.rotation = { 0,3.141592f / 2.0f,0 };

	rock02[0]->wtf.position = { -70,0,250 };
	rock02[0]->wtf.scale = { 2,2,2 };
	rock02[0]->wtf.rotation = { 0,0,0 };

	rock02[1]->wtf.position = { -40,0,240 };
	rock02[1]->wtf.scale = { 1.5f,1.5f,1.5f };
	rock02[1]->wtf.rotation = { 0,220.0f * 3.141592f / 180,0 };
}

TitleField::~TitleField() {
	delete skydome;
	delete skydomeMD;
	delete water;
	delete waterMD;
	delete coast;
	delete coastMD;
	for (int i = 0; i < 2; i++) {
		delete rock01[i];
		delete rock02[i];
	}

	delete rock01MD;
	delete rock02MD;
}

void TitleField::Update() {
	skydome->Update();
	water->Update();
	coast->Update();
	for (int i = 0; i < 2; i++) {
		rock01[i]->Update();
		rock02[i]->Update();
	}
}

void TitleField::Draw() {
	skydome->Draw();
	water->Draw();
	coast->Draw();
	for (int i = 0; i < 2; i++) {
		rock01[i]->Draw();
		rock02[i]->Draw();
	}
}