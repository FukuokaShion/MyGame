/**
 * @file GameScene.h
 * @brief ゲームプレイシーン
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
	~GameScene();

	/**
	 * @brief 初期化
	*/
	void Initialize();

	/**
	 * @brief 更新
	*/
	void Update() override;

	/**
	 * @brief obj描画
	*/
	void ObjectDraw() override;
	
	/**
	 * @brief fbx描画
	*/
	void FbxDraw() override;
	
	/**
	 * @brief スプライト描画
	*/
	void SpriteDraw() override;

private:
	/**
	 * @brief シーン移行
	*/
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