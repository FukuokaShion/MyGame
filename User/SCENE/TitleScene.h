/**
 * @file TitleScene.h
 * @brief タイトルシーン
 */

#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include "Object3d.h"
#include"Audio.h"
#include"TitleField.h"
#include"Ship.h"

class TitleScene : public SceneState {
public:
	TitleScene();
	~TitleScene();

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

private:
	//サウンド
	Audio* audio_ = nullptr;
	IXAudio2SourceVoice* pSourceVoice_ = nullptr;

	//カメラ
	Camera* camera_ = nullptr;

	//画像
	Sprite* basePic_;
	std::unique_ptr<Sprite> black_;
	std::unique_ptr<Sprite> loading_;

	//フィールド
	std::unique_ptr<TitleField> field_;

	//船
	const float blackDrawPos = 60.0f;
	const float blackAddAlpha = 0.04f;
	const float shipMoveEnd = 120.0f;
	std::unique_ptr<Ship> ship_;
};