#include "FBX.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);

	// Lambert反射
	float4 shade_color={0, 0, 0, 1};

	for(int i = 0; i < 3; i++)
	{
		if(dirLights[i].active){
			float3 dotlightnormal = dot(dirLights[i].lightVec,input.normal);
			float3 diffuse = dotlightnormal;

			shade_color.rgb += (diffuse) * dirLights[i].lightColor;
		}
	}

	// 陰影とテクスチャの色を合成
	return shade_color * texcolor;
}