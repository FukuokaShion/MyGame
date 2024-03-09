/**
 * @file LightGroup.h
 * @brief ライト
 */

#pragma once
#include <d3d12.h>
#include <wrl.h>
#include"Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include"DirectionalLight.h"
#include"CircleShadow.h"

namespace MyEngine {
	class LightGroup {
	public:
		static LightGroup* Create();
		static void StaticInitialize(ID3D12Device* device) { device_ = device; }

		void Initialize();
		void Update();
		void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

		void TransferConstBuffer();

		void DefaultLightSetting();

		void SetAmbientColor(const Vector3& color);
		void SetDirLightActive(int index, bool active);
		void SetDirLightDir(int index, Vector4& lightDir);
		void SetDirLightColor(int index, Vector3& lightColor);

		void SetCircleShadowActive(int index, bool active);
		void SetCircleShadowCasterPos(int index, const Vector3& casterPos);
		void SetCircleShadowDir(int index, Vector4& lightDir);
		void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight);
		void SetCircleShadowAtten(int index, const Vector3& lightAtten);
		void SetCircleShadowFactorAngle(int index, const Vector2& lightFactorAngle);

	private:
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	public:
		static const int DirLightNum = 3;
		static const int CircleShadowNum = 1;

		struct ConstBufferData {
			Vector3 ambientColor;
			float pad1;
			DirectionalLight::ConstBufferData dirLights[DirLightNum];
			CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
		};
	private:
		static ID3D12Device* device_;
		HRESULT result;
		ComPtr<ID3D12Resource> constBuff;
		Vector3 ambientColor_ = { 1,1,1 };
		DirectionalLight dirLights_[DirLightNum];
		CircleShadow circleShadows_[CircleShadowNum];
		bool dirty_ = false;
	};
}