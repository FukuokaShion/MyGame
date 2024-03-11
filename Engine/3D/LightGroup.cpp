/**
 * @file LightGroup.cpp
 * @brief ライト
 */

#include"LightGroup.h"

using namespace MyEngine;
ID3D12Device* LightGroup::device_ = nullptr;

void LightGroup::Initialize(){
	DefaultLightSetting();
	// ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	// リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&cbHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	TransferConstBuffer();
}

LightGroup* LightGroup::Create() {
	LightGroup* instance = new LightGroup();
	instance->Initialize();
	return instance;
}

void LightGroup::Update(){
	if (dirty_){
		TransferConstBuffer();
		dirty_ = false;
	}
}

void LightGroup::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex) {
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

void LightGroup::TransferConstBuffer(){
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->ambientColor = ambientColor_;

		/*constMap->pointLightCount = static_cast<uint32_t>(pointLights.size());
		constMap->spotLightCount = static_cast<uint32_t>(spotLights.size());
		constMap->circleShadowCount = static_cast<uint32_t>(circleShadows.size());*/

		//ライト
		for (int i = 0; i < DirLightNum; i++){
			if (dirLights_[i].IsActive()){
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightVec = dirLights_[i].GetLightDir();
				constMap->dirLights[i].lightColor = dirLights_[i].GetLightColor();
			}else{
				constMap->dirLights[i].active = 0;
			}
		}

		//丸影
		for (int i = 0; i < CircleShadowNum; i++){
			if (circleShadows_[i].IsActive()){
				constMap->circleShadows[i].active = 1;
				constMap->circleShadows[i].dir = -circleShadows_[i].GetDir();
				constMap->circleShadows[i].casterPos = circleShadows_[i].GetCasterPos();
				constMap->circleShadows[i].distanceCasterLight = circleShadows_[i].GetDistanceCasterLight();
				constMap->circleShadows[i].atten = circleShadows_[i].GetAtten();
				constMap->circleShadows[i].factorAngleCos = circleShadows_[i].GetFactorAngleCos();
			}else{
				constMap->circleShadows[i].active = 0;
			}
		}

		////スポットライト
		//for (int i = 0; i < spotLights.size(); i++)
		//{
		//	//ライトが有効なら設定を転送
		//	if (spotLights[i].IsActive())
		//	{
		//		constMap->spotLights[i].active = 1;
		//		constMap->spotLights[i].lightv = -spotLights[i].GetLightDir();
		//		constMap->spotLights[i].lightpos = spotLights[i].GetLightPos();
		//		constMap->spotLights[i].lightcolor = spotLights[i].GetLightColor();
		//		constMap->spotLights[i].lightatten = spotLights[i].GetLightAtten();
		//		constMap->spotLights[i].lightfactoranglecos = spotLights[i].GetLightFactorAngleCos();
		//	}
		//	else
		//	{//ライトが無効ならライトを0に
		//		constMap->spotLights[i].active = 0;
		//	}
		//}

		constBuff->Unmap(0, nullptr);
	}

}

void LightGroup::SetAmbientColor(const Vector3& color) {
	ambientColor_ = color;
	dirty_ = true;
}

void LightGroup::SetDirLightActive(int index, bool active) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetActive(active);
}

void LightGroup::SetDirLightDir(int index, Vector4& lightDir) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightDir(lightDir);
	dirty_ = true;
}

void LightGroup::SetDirLightColor(int index, Vector3& lightColor) {
	assert(0 <= index && index < DirLightNum);
	dirLights_[index].SetLightColor(lightColor);
	dirty_ = true;
}

void LightGroup::DefaultLightSetting() {
	dirLights_[0].SetActive(true);
	dirLights_[0].SetLightColor({ 1, 1, 1 });
	dirLights_[0].SetLightDir({ 0,1,-1,0 });

	dirLights_[1].SetActive(false);
	dirLights_[1].SetLightColor({ 1, 1, 1 });
	dirLights_[1].SetLightDir({ 0,-1,0,0 });

	dirLights_[2].SetActive(false);
	dirLights_[2].SetLightColor({ 1, 1, 1 });
	dirLights_[2].SetLightDir({ 1,1,0,0 });
}

void LightGroup::SetCircleShadowActive(int index, bool active) {
	assert(0 <= index && index < CircleShadowNum);
	circleShadows_[index].SetActive(active);
}

void LightGroup::SetCircleShadowCasterPos(int index, const Vector3& casterPos) {
	assert(0 <= index && index < CircleShadowNum);
	circleShadows_[index].SetCasterPos(casterPos);
	dirty_ = true;
}

void LightGroup::SetCircleShadowDir(int index, Vector4& lightDir) {
	assert(0 <= index && index < CircleShadowNum);
	circleShadows_[index].SetDir(lightDir);
	dirty_ = true;
}

void LightGroup::SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight) {
	assert(0 <= index && index < CircleShadowNum);
	circleShadows_[index].SetDistanceCasterLight(distanceCasterLight);
	dirty_ = true;
}

void LightGroup::SetCircleShadowAtten(int index, const Vector3& lightAtten) {
	assert(0 <= index && index < CircleShadowNum);
	circleShadows_[index].SetAtten(lightAtten);
	dirty_ = true;
}

void LightGroup::SetCircleShadowFactorAngle(int index, const Vector2& lightFactorAngle) {
	assert(0 <= index && index < CircleShadowNum);
	circleShadows_[index].SetFactorAngle(lightFactorAngle);
	dirty_ = true;
}