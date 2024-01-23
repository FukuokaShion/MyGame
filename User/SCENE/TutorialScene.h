/**
 * @file TutorialScene.h
 * @brief チュートリアルシーン
 */

#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include"Audio.h"

#include"TutorialField.h"
#include"Player.h"
#include"CollisionManager.h"
#include"GameCamera.h"
#include"Option.h"

using namespace std;

class TutorialScene : public SceneState {
public:
	TutorialScene();
	~TutorialScene();

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
		option,
		departure,
	};
private:
	State state_;

	//サウンド
	unique_ptr<Audio> audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;

	//メンバ変数
	//カメラ
	unique_ptr<GameCamera> gameCamera_ = nullptr;
	unique_ptr<Camera> camera_ = nullptr;
	//フィールド
	unique_ptr<TutorialField> field_ = nullptr;

	//プレイヤー
	unique_ptr<Player> player_ = nullptr;

	//画像
	unique_ptr<Sprite> pushB_;

	//オプション
	unique_ptr<Option> option_ = nullptr;

	Vector3 shipPos_;
	const float fadeOutPos = 40.0f;
	unique_ptr<Ship> ship_ = nullptr;
};