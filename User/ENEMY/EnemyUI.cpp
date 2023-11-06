/**
 * @file EnemyUI.cpp
 * @brief エネミーのUI管理クラス
 */

#include"EnemyUI.h"

void EnemyUI::Initialize() {
	//スプライト
	base_ = new Sprite();
	base_->Initialize(SpriteCommon::GetInstance());
	base_->SetSize({ 1280,720 });

	enemyHpGauge_ = new Sprite();
	enemyHpGauge_->Initialize(SpriteCommon::GetInstance());
	enemyHpGauge_->SetPozition({ 309,576 });
	enemyHpGauge_->SetSize({ 671,11 });
	enemyHpGauge_->SetColor({ 172.0f / 255.0f,50.0f / 255.0f,50.0f / 255.0f,1.0f });

	base_->SetTextureIndex(3);
	enemyHpGauge_->SetTextureIndex(0);
}

EnemyUI::~EnemyUI() {
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