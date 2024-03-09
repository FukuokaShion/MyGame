#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float3 ambient = m_ambient;
	float3 shade_color = ambient;

	float4 texcolor = tex.Sample(smp, input.uv);

	for(int i = 0; i < 3; i++)
	{
		if(dirLights[i].active){
			float3 dotlightnormal = dot(dirLights[i].lightVec,input.normal);
			float3 diffuse = dotlightnormal * m_diffuse;

			shade_color.rgb += (diffuse) * dirLights[i].lightColor;
		}
	}

	return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);
}