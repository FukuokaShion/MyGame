/**
 * @file LoaderManager.cpp
 * @brief 様々なものの読み込み管理
 */
#include"LoaderManager.h"
#include"ObjModelLoader.h"

void LoaderManager::Initilize() {
	objModels = ObjModelLoader::GetInstance();
}

void LoaderManager::Finalize() {
	objModels->Finalize();
}

void LoaderManager::Load() {
	ObjLoad();

}

void LoaderManager::ObjLoad() {

}