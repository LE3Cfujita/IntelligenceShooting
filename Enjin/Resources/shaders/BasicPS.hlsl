#include "Basic.hlsli"

/* 
cbuffer cbuff0:register(b0)
{
	float4 color;	//色(RGBA)
};

float4 main() : SV_TARGET
{
	return color;
}
*/
Texture2D<float4> tex : register(t0);	//
SamplerState smp : register(s0);		//

float4 main(VSOutput input) : SV_TARGET
{
	float3 light = normalize(float3(1,-1,1));				//右下奥　向きのライト
	float diffuse = saturate(dot(-light, input.normal));	//diffuseを[0,1]の範囲にClampする
	float brightness = diffuse + 0.3f;						//アンビエント項を0.3として計算
	float4 texcolor = float4(tex.Sample(smp, input.uv));
	return float4(texcolor.rgb * brightness, texcolor.a) * color;
	//return float4(tex.Sample(smp,input.uv)) * float4(1,0,0,1);
	//return float4(tex.Sample(smp, input.uv));
	//return float4(input.normal,1);	//RGBをそれぞれ法線のXYZ、Aを1で出力
}