/**
 * @file TitleScene.h
 * @brief タイトルシーン
 */

#pragma once
#include"SceneState.h"
#include"Sprite.h"
#include "Object3d.h"
#include"Audio.h"

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

	//obj
	Object3d* skydome = nullptr;
	Model* skydomeMD = nullptr;
	Object3d* water = nullptr;
	Model* waterMD = nullptr;
	Object3d* coast = nullptr;
	Model* coastMD = nullptr;

	Object3d* rock01[2];
	Model* rock01MD = nullptr;
	Object3d* rock02[2];
	Model* rock02MD = nullptr;

	//船
	Object3d* ship = nullptr;
	Model* shipMD = nullptr;
	float shipAngle;
	bool isMoveShip;
	float shipSpeed;
	int timer;
	int limit;

	//プレイヤー
	Object3d* player = nullptr;
	Model* playerMD = nullptr;
};