#include"Field.h"

Field::Field() {

}

void Field::Initialize() {
	//”wŒi
	floorMD = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorMD);
	floor->wtf.position = (Vector3{ 0, -10, 0 });

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });

}

Field::~Field() {
	delete floor;
	delete floorMD;
	delete skydome;
	delete skydomeMD;
}

void Field::Update() {
	floor->Update();
	skydome->Update();
}

void Field::Draw() {
	floor->Draw();
	skydome->Draw();
}