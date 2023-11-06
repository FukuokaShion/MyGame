/**
 * @file SpriteLoader.cpp
 * @brief スプライト読み込み
 */

#include"SpriteLoader.h"

void SpriteLoader::Load() {
	SpriteCommon::GetInstance()->Initialize();

	SpriteCommon::GetInstance()->LoadTexture(0, "white.png");
	SpriteCommon::GetInstance()->LoadTexture(1, "title.png");
	SpriteCommon::GetInstance()->LoadTexture(2, "loading.png");
	SpriteCommon::GetInstance()->LoadTexture(3, "enemyUI.png");
	SpriteCommon::GetInstance()->LoadTexture(4, "playerUI.png");
	SpriteCommon::GetInstance()->LoadTexture(5, "clear.png");
	SpriteCommon::GetInstance()->LoadTexture(6, "gameOver.png");
}