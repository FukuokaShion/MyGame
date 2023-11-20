/**
 * @file SpriteLoader.h
 * @brief スプライト読み込み
 */

#pragma once
#include"Sprite.h"

class SpriteLoader {
public:
	enum {
		WHITE,
		TITLE,
		LOADING,
		ENEMYUI,
		PLAYERUI,
		CLEAR,
		GAMEOVER,
		OPTION,
		RSTICK
	};

	/**
	 * @brief 読み込み
	*/
	static void Load();
};