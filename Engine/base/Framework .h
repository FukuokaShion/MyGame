/**
 * Framework.h
 * エンジンフレームワーク
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

	virtual void Initialize();

	void Run();

protected:
	virtual void Finalize();

	virtual void Update();

	virtual void Draw();

	virtual bool IsEndRequst();

protected:
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
};