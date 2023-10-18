/**
 * @file Framework.h
 * @brief エンジンフレームワーク
 */

#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Input.h"

class Framework {
public:
	virtual ~Framework() = default;
	Framework() = default;

	/**
	 * @brief 初期化
	*/
	virtual void Initialize();

	/**
	 * @brief 稼働
	*/
	void Run();

protected:
	/**
	 * @brief 破棄
	*/
	virtual void Finalize();

	/**
	 * @brief 更新
	*/
	virtual void Update();

	/**
	 * @brief 描画
	*/
	virtual void Draw();

	/**
	 * @brief 終了フラグ
	*/
	virtual bool IsEndRequst();

protected:
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
};