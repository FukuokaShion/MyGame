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
		BOSSFELLED,
		YOUDIED,
		OPTION,
		RSTICK,
		TELOPBASE,
		PUSHB,
		ARROW,
	};

	/**
	 * @brief 読み込み
	*/
	static void Load();
};