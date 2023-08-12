#pragma once
#pragma once
#include "SceneState.h"
#include "DirectXCommon.h"
#include <string>
#include "Input.h"
#include "Matrix4.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include "Audio.h"

#include "Camera.h"
#include "Object3d.h"
#include "Model.h"
#include "FBXObject3d.h"

/// <summary>
/// ゲームシーン
/// </summary>
class SceneManager
{
private: // 静的メンバ変数

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon);

	//状態移行
	void TransitionTo(SceneState* state);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

private: //メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;

	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;

private:
	//カメラ
	Camera* camera = nullptr;

	//シーン
	SceneState* state_ = nullptr;
	
};