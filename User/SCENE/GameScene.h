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

	CollisionManager* collisionManager_ = nullptr;

	//クリア
	Sprite* clear_;
	const float clearAddAlpha_ = 0.005f;

	//ゲームオーバー
	Sprite* gameOver_;
	bool isGameOver;
	std::unique_ptr<Sprite> black_;
	std::unique_ptr<Sprite> loading_;
	const float gameOverAddAlpha_ = 0.01f;
	const float gameOverAlphaEnd_ = 0.6f;
	const float blackAddAlpha_ = 0.04f;


};