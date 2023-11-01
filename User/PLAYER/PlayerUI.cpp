/**
 * @file PlayerUI.cpp
 * @brief プレイヤーのUI管理クラス
 */

#include"PlayerUI.h"

void PlayerUI::Initialize() {
	//スプライト共通部分の初期化
	spriteCommon_ = new SpriteCommon;
	spriteCommon_->Initialize();

	//スプライト
	base_ = new Sprite();
	base_->Initialize(spriteCommon_);
	base_->SetSize({ 1280,720 });

	hpGauge_ = new Sprite();
	hpGauge_->Initialize(spriteCommon_);
	hpGauge_->SetPozition({ 128,38 });
	hpGauge_->SetSize({ 400,26 });
	hpGauge_->SetColor({ 106.0f / 255.0f,190.0f / 255.0f,48.0f / 255.0f,1.0f });

	damageGauge_ = new Sprite();
	damageGauge_->Initialize(spriteCommon_);
	damageGauge_->SetPozition({ 128,38 });
	damageGauge_->SetSize({ 400,26 });
	damageGauge_->SetColor({ 255.0f / 255.0f,255.0f / 255.0f,3.0f / 255.0f,1.0f });

	spriteCommon_->LoadTexture(0, "UI.png");
	base_->SetTextureIndex(0);

	spriteCommon_->LoadTexture(1, "white.png");
	hpGauge_->SetTextureIndex(1);

	spriteCommon_->LoadTexture(2, "white.png");
	damageGauge_->SetTextureIndex(2);
}

PlayerUI::~PlayerUI() {
	delete spriteCommon_;
	
	delete hpGauge_;
	delete damageGauge_;
	delete base_;
}

void PlayerUI::Update(int a, int b) {
	base_->Update();
	damageGauge_->SetSize({ static_cast<float>(4 * a),26 });
	hpGauge_->SetSize({ static_cast<float>(4 * b),26 });

}

void PlayerUI::Draw() {
	base_->Draw();
	damageGauge_->Draw();
	hpGauge_->Draw();
}