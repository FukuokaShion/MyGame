/**
 * @file LoaderManager.cpp
 * @brief 様々なものの読み込み管理
 */
#include"LoaderManager.h"
#include"ObjModelLoader.h"

void LoaderManager::Initilize() {
	objModels_ = ObjModelLoader::GetInstance();
}

void LoaderManager::Finalize() {
	objModels_->Finalize();
}

void LoaderManager::Load() {
	ObjLoad();

}

void LoaderManager::ObjLoad() {

}