/**
 * GameScene.h
 * ゲームプレイシーン
 */

#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include"Audio.h"

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

	enum class State {
		game,
		clear,
		death,
	};
private:
	State state;

	//画像
	SpriteCommon* spriteCommon = nullptr;
	//サウンド
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice = nullptr;

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

	Sprite* clear;
	Sprite* gameOver;

	CollisionManager* collisionManager = nullptr;
};