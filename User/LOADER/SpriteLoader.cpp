/**
 * @file SpriteLoader.cpp
 * @brief スプライト読み込み
 */

#include"SpriteLoader.h"

void SpriteLoader::Load() {
	SpriteCommon::GetInstance()->Initialize();

	SpriteCommon::GetInstance()->LoadTexture(WHITE, "white.png");
	SpriteCommon::GetInstance()->LoadTexture(TITLE, "title.png");
	SpriteCommon::GetInstance()->LoadTexture(LOADING, "loading.png");
	SpriteCommon::GetInstance()->LoadTexture(ENEMYUI, "enemyUI.png");
	SpriteCommon::GetInstance()->LoadTexture(PLAYERUI, "playerUI.png");
	SpriteCommon::GetInstance()->LoadTexture(BOSSFELLED, "bossFelled.png");
	SpriteCommon::GetInstance()->LoadTexture(YOUDIED, "youDied.png");
	SpriteCommon::GetInstance()->LoadTexture(OPTION, "option.png");
	SpriteCommon::GetInstance()->LoadTexture(RSTICK, "r.png");
	SpriteCommon::GetInstance()->LoadTexture(TELOPBASE, "telopBase.png");
	SpriteCommon::GetInstance()->LoadTexture(PUSHB, "pushB.png");
	SpriteCommon::GetInstance()->LoadTexture(ARROW, "arrow.png");
}