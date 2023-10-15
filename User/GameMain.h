/**
 * GameMain.h
 * ゲーム全体の流れ
 */

#pragma once
#include"Framework .h"
#include"SceneManager.h"

class GameMain : public Framework {
public:
	GameMain();
	~GameMain();

	virtual void Initialize();

private:
	void Finalize() override;

	void Update() override;

	void Draw() override;

	bool IsEndRequst() override;

private:
	SceneManager* sceneManager = nullptr;
};