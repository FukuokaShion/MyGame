/**
 * @file ship.cpp
 * @brief タイトルシーン
 */

#include"Ship.h"
#include"Easing.h"

void Ship::Initialize() {
	shipMD_ = Model::LoadFromOBJ("ship");
	ship_ = Object3d::Create();
	ship_->SetModel(shipMD_);
	ship_->wtf.position = { -20,0,28 };
	shipAngle_ = 0.04f * 3.141592f / 180.0f;
	shipSpeed_ = 0.3f;
	timer_ = 0;
	limit_ = 90;

	playerMD_ = Model::LoadFromOBJ("playerObj");
	player_ = Object3d::Create();
	player_->SetModel(playerMD_);
	player_->wtf.position = { -20,0.5f,28 };

	input_ = Input::GetInstance();
}

Ship::~Ship() {
	delete ship_;
	delete shipMD_;
	delete player_;
	delete playerMD_;
}

void Ship::Update() {

	const float shipRotaMax = 4 * 3.141592f / 180;
	if (abs(ship_->wtf.rotation.x) > shipRotaMax) {
		shipAngle_ *= -1;
	}
	ship_->wtf.rotation.x += shipAngle_;
	ship_->Update();

	player_->Update();

	if (isMoveShip_) {
		if (timer_ < limit_) {
			timer_++;
		}

		float t = static_cast<float>(timer_) / static_cast<float>(limit_);
		float add = Easing::OutQuad(0, shipSpeed_, t);

		ship_->wtf.position.z += add;
		player_->wtf.position.z += add;
	}
}

void Ship::Draw() {
	player_->Draw();
	ship_->Draw();
}