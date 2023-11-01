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
	State state_;

	//画像
	SpriteCommon* spriteCommon_ = nullptr;
	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;

	//メンバ変数
	//カメラ
	Camera* camera_ = nullptr;
	//フィールド
	Field* field_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;
	//エネミー
	Enemy* enemy_ = nullptr;

	//画像
	Sprite* UiBase_;
	Sprite* hpGauge_;
	Sprite* damageGauge_;
	Sprite* enemyHpGauge_;
	Sprite* clear_;
	Sprite* gameOver_;

	CollisionManager* collisionManager_ = nullptr;

	//ゲームオーバー
	bool isGameOver;
	std::unique_ptr<Sprite> black_;
	std::unique_ptr<Sprite> loading_;

};