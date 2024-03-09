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
	
	//丸影
	for(int i = 0; i < CIRCLESHADOW_NUM; i++)
	{
		if(circleShadows[i].active){
			//オブジェクト表面からキャスターへのベクトル
			float3 casterVec  = circleShadows[i].casterPos - input.worldpos.xyz;
			//東映方向での減衰
			float d = dot(casterVec, circleShadows[i].dir);
			//距離減衰係数
			float atten = saturate(1.0f/(circleShadows[i].atten.x + circleShadows[i].atten.y*d+circleShadows[i].atten.z*d*d));
			//距離がminusなら0にする
			atten *= step(0, d);
			//仮想ライトの座標
			float3 lightPos = circleShadows[i].casterPos + circleShadows[i].dir * circleShadows[i].distanceCasterLight;
			//オブジェクト表面からライトへのベクトル
			float3 lightVec = normalize(lightPos - input.worldpos.xyz);
			//角度減衰
			float cos = dot(lightVec, circleShadows[i].dir);
			//減衰開始角度から、減衰終了角度にかけて減衰
			float angleatten = smoothstep(circleShadows[i].factorAngleCos.y, circleShadows[i].factorAngleCos.x, cos);
			//角度減衰を乗算
			atten *= angleatten;
			
			shade_color.rgb -= atten;
		}
	}

	return float4(texcolor.rgb * shade_color, texcolor.a * m_alpha);
}