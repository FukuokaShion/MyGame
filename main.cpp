/**
 * @file Main.cpp
 * @brief　ゲームを動かす
 */

#include "GameMain.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	GameMain game;

	game.Run();

	return 0;
}