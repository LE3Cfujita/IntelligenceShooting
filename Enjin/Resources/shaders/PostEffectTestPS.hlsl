#include "PostEffectTest.hlsli"

Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t1);  // 1番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー


float4 main(VSOutput input) : SV_TARGET
{
	//色合計用の変数を(0,0,0,0)で初期化
	float4 texcolor = tex.Sample(smp, input.uv);
	return  float4(texcolor.rgb * 2.0f, 1);
}