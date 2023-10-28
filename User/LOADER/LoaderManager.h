/**
 * @file LoaderManager.cpp
 * @brief 様々なものの読み込み管理
 */

#pragma once
#include"ObjModelLoader.h"

class LoaderManager {
public:
	void Finalize();

	/**
	 * @brief 初期化
	*/
	void Initilize();
	
	/**
	 * @brief 全部読み込み
	*/
	void Load();

private:
	/**
	 * @brief objモデル読み込み
	*/
	void ObjLoad();

private:
	ObjModelLoader* objModels;
};