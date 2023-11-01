/**
 * @file EnemyUI.cpp
 * @brief エネミーのUI管理クラス
 */

#include"EnemyUI.h"

void EnemyUI::Initialize() {
	//スプライト共通部分の初期化
	spriteCommon_ = new SpriteCommon;
	spriteCommon_->Initialize();

	//スプライト
	base_ = new Sprite();
	base_->Initialize(spriteCommon_);
	base_->SetSize({ 1280,720 });

	enemyHpGauge_ = new Sprite();
	enemyHpGauge_->Initialize(spriteCommon_);
	enemyHpGauge_->SetPozition({ 309,576 });
	enemyHpGauge_->SetSize({ 671,11 });
	enemyHpGauge_->SetColor({ 172.0f / 255.0f,50.0f / 255.0f,50.0f / 255.0f,1.0f });

	spriteCommon_->LoadTexture(0, "enemyUI.png");
	base_->SetTextureIndex(0);

	spriteCommon_->LoadTexture(3, "white.png");
	enemyHpGauge_->SetTextureIndex(3);
}

EnemyUI::~EnemyUI() {
	delete spriteCommon_;

	delete base_;
	delete enemyHpGauge_;
}

void EnemyUI::Update(int hp) {
	base_->Update();
	enemyHpGauge_->SetSize({ static_cast<float>(6.71f * hp),11 });
}

void EnemyUI::Draw() {
	base_->Draw();
	enemyHpGauge_->Draw();
}