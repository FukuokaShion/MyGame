/**
 * @file TutorialField.cpp
 * @brief チュートリアルシーンのステージ描画
 */

#include"TutorialField.h"
#include"SpriteLoader.h"

TutorialField::TutorialField() {

}

void TutorialField::Initialize() {
	scarecrow_ = std::make_unique<Scarecrow>();
	scarecrow_->Initialize();

	jampBoard_ = make_unique<Signboard>();
	jampBoard_->Initialize(SpriteLoader::TUTORIAL_JUMP);
	jampBoard_->SetPos({-20,0,0});
	jampBoard_->SetRota({0,0,0});
	attackBoard_ = make_unique<Signboard>();
	attackBoard_->Initialize(SpriteLoader::TUTORIAL_ATTACK);
	attackBoard_->SetPos({ -10,0,0 });
	attackBoard_->SetRota({ 0,0,0 });
	rollingBoard_ = make_unique<Signboard>();
	rollingBoard_->Initialize(SpriteLoader::TUTORIAL_ROLLING);
	rollingBoard_->SetPos({ 10,0,0 });
	rollingBoard_->SetRota({ 0,0,0 });
	cameraBoard_ = make_unique<Signboard>();
	cameraBoard_->Initialize(SpriteLoader::TUTORIAL_CAMERA);
	cameraBoard_->SetPos({ 20,0,0 });
	cameraBoard_->SetRota({ 0,0,0 });

	//背景
	skydomeMD_ = Model::LoadFromOBJ("skydome");
	skydome_ = Object3d::Create();
	skydome_->SetModel(skydomeMD_.get());
	skydome_->wtf.scale = (Vector3{ 1000, 1000, 1000 });

	waterMD_ = Model::LoadFromOBJ("water");
	water_ = Object3d::Create();
	water_->SetModel(waterMD_.get());
	water_->wtf.scale = { 2,1,2 };

	coastMD_ = Model::LoadFromOBJ("coast");
	coast_ = Object3d::Create();
	coast_->SetModel(coastMD_.get());
	coast_->wtf.scale = { 2,1,2 };
	coast_->wtf.rotation.y = 3.14f;

	rock01MD_ = Model::LoadFromOBJ("rock01");
	rock02MD_ = Model::LoadFromOBJ("rock02");

	for (int i = 0; i < 2; i++) {
		rock01_[i] = Object3d::Create();
		rock01_[i]->SetModel(rock01MD_.get());
		rock02_[i] = Object3d::Create();
		rock02_[i]->SetModel(rock02MD_.get());
	}

	rock01_[0]->wtf.position = { -50,0,240 };
	rock01_[0]->wtf.scale = { 1.4f,1,1 };
	rock01_[0]->wtf.rotation = { 0,0,0 };

	rock01_[1]->wtf.position = { -60,0,250 };
	rock01_[1]->wtf.scale = { 1,1.3f,1.2f };
	rock01_[1]->wtf.rotation = { 0,3.141592f / 2.0f,0 };

	rock02_[0]->wtf.position = { -70,0,250 };
	rock02_[0]->wtf.scale = { 2,2,2 };
	rock02_[0]->wtf.rotation = { 0,0,0 };

	rock02_[1]->wtf.position = { -40,0,240 };
	rock02_[1]->wtf.scale = { 1.5f,1.5f,1.5f };
	rock02_[1]->wtf.rotation = { 0,220.0f * 3.141592f / 180,0 };


	bushMD_ = Model::LoadFromOBJ("bush");
	for (int i = 0; i < bushNum_; i++) {
		bush_[i] = Object3d::Create();
		bush_[i]->SetModel(bushMD_.get());
	}
	bush_[0]->wtf.position = { 50,0,0 };
	bush_[0]->wtf.scale = { 1,1,1 };
	bush_[0]->wtf.rotation = { 0,0,0 };
	bush_[1]->wtf.position = { 27.6f,0,-10.02f };
	bush_[1]->wtf.scale = { 1,1,2 };
	bush_[1]->wtf.rotation = { 0,0,0 };
	bush_[2]->wtf.position = { 15,0,-25.8f };
	bush_[2]->wtf.scale = { 1,1,4 };
	bush_[2]->wtf.rotation = { 0,0,0 };
	bush_[3]->wtf.position = { 5.4f,0,-29.4f };
	bush_[3]->wtf.scale = { 1,1,3 };
	bush_[3]->wtf.rotation = { 0,0,0 };
	bush_[4]->wtf.position = { 0,0,-30 };
	bush_[4]->wtf.scale = { 1,1,2 };
	bush_[4]->wtf.rotation = { 0,0,0 };
	bush_[5]->wtf.position = { -10.2f,0,-27.6f };
	bush_[5]->wtf.scale = { 1,1,1.5f };
	bush_[5]->wtf.rotation = { 0,0,0 };
	bush_[6]->wtf.position = { -24.6f,0,-16.8f };
	bush_[6]->wtf.scale = { 1,1,3 };
	bush_[6]->wtf.rotation = { 0,0,0 };
	bush_[7]->wtf.position = { -29.4f,0,-4.8f };
	bush_[7]->wtf.scale = { 1,1,2 };
	bush_[7]->wtf.rotation = { 0,0,0 };
	bush_[8]->wtf.position = { -19.2f,0,-22.8f };
	bush_[8]->wtf.scale = { 1,1,4 };
	bush_[8]->wtf.rotation = { 0,0,0 };
	bush_[9]->wtf.position = { -30,0,0 };
	bush_[9]->wtf.scale = { 1,1,2 };
	bush_[9]->wtf.rotation = { 0,0,0 };

	//palmTreeMD_ = Model::LoadFromOBJ("palmtree");
	//for (int i = 0; i < palmTreeNum_; i++) {
	//	palmTree_[i] = Object3d::Create();
	//	palmTree_[i]->SetModel(palmTreeMD_.get());
	//}
	//palmTree_[0]->wtf.position = { 0,0,0 };
	//palmTree_[1]->wtf.position = { 0,0,0 };
	//palmTree_[2]->wtf.position = { 0,0,0 };
	//palmTree_[3]->wtf.position = { 0,0,0 };
	//palmTree_[4]->wtf.position = { 0,0,0 };
	//palmTree_[5]->wtf.position = { 0,0,0 };
	//palmTree_[6]->wtf.position = { 0,0,0 };
	//palmTree_[7]->wtf.position = { 0,0,0 };
	//palmTree_[8]->wtf.position = { 0,0,0 };
	//palmTree_[9]->wtf.position = { 0,0,0 };
}

TutorialField::~TutorialField() {}

void TutorialField::Update() {
	scarecrow_->Update();
	jampBoard_->Update();
	jampBoard_->CheckCol(playerPos_);
	attackBoard_->Update();
	attackBoard_->CheckCol(playerPos_);
	rollingBoard_->Update();
	rollingBoard_->CheckCol(playerPos_);
	cameraBoard_->Update();
	cameraBoard_->CheckCol(playerPos_);

	skydome_->Update();
	water_->Update();
	coast_->Update();
	for (int i = 0; i < 2; i++) {
		rock01_[i]->Update();
		rock02_[i]->Update();
	}

	for (int i = 0; i < bushNum_; i++) {
		bush_[i]->Update();
	}
	//for (int i = 0; i < palmTreeNum_; i++) {
	//	palmTree_[i]->Update();
	//}
}

void TutorialField::ObjDraw() {
	scarecrow_->Draw();
	jampBoard_->ObjDraw();
	attackBoard_->ObjDraw();
	rollingBoard_->ObjDraw();
	cameraBoard_->ObjDraw();

	skydome_->Draw();
	water_->Draw();
	coast_->Draw();
	for (int i = 0; i < 2; i++) {
		rock01_[i]->Draw();
		rock02_[i]->Draw();
	}
	for (int i = 0; i < bushNum_; i++) {
		bush_[i]->Draw();
	}
	//for (int i = 0; i < palmTreeNum_; i++) {
	//	palmTree_[i]->Draw();
	//}
}

void TutorialField::SpriteDraw() {
	jampBoard_->SpriteDraw();
	attackBoard_->SpriteDraw();
	rollingBoard_->SpriteDraw();
	cameraBoard_->SpriteDraw();
}