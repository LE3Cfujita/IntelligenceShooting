#include "Basic.hlsli"

/* 
cbuffer cbuff0:register(b0)
{
	float4 color;	//�F(RGBA)
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
	float3 light = normalize(float3(1,-1,1));				//�E�����@�����̃��C�g
	float diffuse = saturate(dot(-light, input.normal));	//diffuse��[0,1]�͈̔͂�Clamp����
	float brightness = diffuse + 0.3f;						//�A���r�G���g����0.3�Ƃ��Čv�Z
	float4 texcolor = float4(tex.Sample(smp, input.uv));
	return float4(texcolor.rgb * brightness, texcolor.a) * color;
	//return float4(tex.Sample(smp,input.uv)) * float4(1,0,0,1);
	//return float4(tex.Sample(smp, input.uv));
	//return float4(input.normal,1);	//RGB�����ꂼ��@����XYZ�AA��1�ŏo��
}