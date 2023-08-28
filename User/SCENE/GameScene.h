#pragma once
#include"SceneState.h"
#include"Sprite.h"

#include"Field.h"
#include"Player.h"
#include"Enemy.h"
#include"CollisionManager.h"

class GameScene : public SceneState {
public:
	GameScene();
	void Initialize();
	~GameScene();

	//更新
	void Update() override;

	//描画
	void ObjectDraw() override;
	void FbxDraw() override;
	void SpriteDraw() override;

private:
	void StateTransition() override;

private:
	//画像
	SpriteCommon* spriteCommon = nullptr;

	//メンバ変数
	//カメラ
	Camera* camera = nullptr;
	//フィールド
	Field* field = nullptr;

	//プレイヤー
	Player* player = nullptr;
	//エネミー
	Enemy* enemy = nullptr;

	//画像
	Sprite* UIBase;

	Sprite* hpGauge;
	Sprite* damageGauge;
	Sprite* enemyHpGauge;

	CollisionManager* collisionManager = nullptr;
};