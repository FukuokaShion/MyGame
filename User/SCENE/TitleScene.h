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
	Audio* audio = nullptr;
	IXAudio2SourceVoice* pSourceVoice = nullptr;

	//カメラ
	Camera* camera = nullptr;

	//画像
	SpriteCommon* spriteCommon = nullptr;
	Sprite* basePic;
	std::unique_ptr<Sprite> black;
	std::unique_ptr<Sprite> loading;

	//フィールド
	std::unique_ptr<TitleField> field;

	//船
	std::unique_ptr<Ship> ship;

};