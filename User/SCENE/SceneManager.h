#pragma once
#include "SceneState.h"
#include "DirectXCommon.h"

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
private: //メンバ変数 (固定)
	DirectXCommon* dxCommon = nullptr;

private:
	//シーン
	SceneState* state_ = nullptr;
	
};