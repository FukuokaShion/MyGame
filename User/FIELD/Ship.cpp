/**
 * @file ship.cpp
 * @brief タイトルシーン
 */

#include"Ship.h"
#include"Easing.h"

void Ship::Initialize() {
	shipMD = Model::LoadFromOBJ("ship");
	ship = Object3d::Create();
	ship->SetModel(shipMD);
	ship->wtf.position = { -20,0,28 };
	shipAngle = 0.04f * 3.141592f / 180.0f;
	shipSpeed = 0.3f;
	timer = 0;
	limit = 90;

	playerMD = Model::LoadFromOBJ("playerObj");
	player = Object3d::Create();
	player->SetModel(playerMD);
	player->wtf.position = { -20,0.5f,28 };

	input_ = Input::GetInstance();
}

Ship::~Ship() {
	delete ship;
	delete shipMD;
	delete player;
	delete playerMD;
}

void Ship::Update() {
	if (abs(ship->wtf.rotation.x) > 4 * 3.141592f / 180) {
		shipAngle *= -1;
	}
	ship->wtf.rotation.x += shipAngle;
	ship->Update();

	player->Update();

	if (input_->PButtonTrigger(B)) {
		isMoveShip = true;
	}

	if (isMoveShip) {
		if (timer < limit) {
			timer++;
		}

		float t = static_cast<float>(timer) / static_cast<float>(limit);
		float add = Easing::OutQuad(0, shipSpeed, t);

		ship->wtf.position.z += add;
		player->wtf.position.z += add;
	}
}

void Ship::Draw() {
	player->Draw();
	ship->Draw();
}