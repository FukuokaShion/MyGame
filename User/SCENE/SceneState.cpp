/**
 * @file SceneState.cpp
 * @brief シーンのステートパターン基底
 */

#include"SceneState.h"

SceneManager* SceneState::sceneManager = nullptr;

SceneState::SceneState() {
	input = Input::GetInstance();
}