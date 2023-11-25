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
#include"GameCamera.h"
#include"Option.h"

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
		option,
	};
private:
	State state_;

	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;

	//メンバ変数
	//カメラ
	GameCamera* gameCamera_ = nullptr;
	//フィールド
	Field* field_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;
	//エネミー
	Enemy* enemy_ = nullptr;

	CollisionManager* collisionManager_ = nullptr;


	//画像
	Sprite* pushB_;
	Sprite* telopBase_;
	float telopBaseAddAlpha_;

	//クリア
	Sprite* clear_;
	const float clearAddAlpha_ = 0.005f;

	//ゲームオーバー
	Sprite* youDiedPic_;
	float youDiedAddAlpha_;

	//オプション
	Option* option_ = nullptr;

};