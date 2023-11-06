/**
 * @file PlayerUI.cpp
 * @brief プレイヤーのUI管理クラス
 */

#include"PlayerUI.h"

void PlayerUI::Initialize() {
	//スプライト
	base_ = new Sprite();
	base_->Initialize(SpriteCommon::GetInstance());
	base_->SetSize({ 1280,720 });

	hpGauge_ = new Sprite();
	hpGauge_->Initialize(SpriteCommon::GetInstance());
	hpGauge_->SetPozition({ 128,38 });
	hpGauge_->SetSize({ 400,26 });
	hpGauge_->SetColor({ 106.0f / 255.0f,190.0f / 255.0f,48.0f / 255.0f,1.0f });

	damageGauge_ = new Sprite();
	damageGauge_->Initialize(SpriteCommon::GetInstance());
	damageGauge_->SetPozition({ 128,38 });
	damageGauge_->SetSize({ 400,26 });
	damageGauge_->SetColor({ 255.0f / 255.0f,255.0f / 255.0f,3.0f / 255.0f,1.0f });

	base_->SetTextureIndex(4);
	hpGauge_->SetTextureIndex(0);
	damageGauge_->SetTextureIndex(0);
}

PlayerUI::~PlayerUI() {
	
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