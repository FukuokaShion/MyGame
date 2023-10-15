/**
 * SceneState.cpp
 * シーンのステートパターン基底
 */

#include"SceneState.h"

Input* SceneState::input = nullptr;
SceneManager* SceneState::sceneManager = nullptr;

SceneState::SceneState() {
}