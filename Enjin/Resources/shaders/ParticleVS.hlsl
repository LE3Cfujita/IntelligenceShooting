#include "Particle.hlsli"

VSOutput main(
	float4 pos : POSITION,
	float scaleX : SCALEX,
	float scaleY : SCALEY,
	float4 color : COLOR,
	float rotation : ROTATION)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.pos = pos;
	output.scaleX = scaleX;
	output.scaleY = scaleY;
	output.color = color;
	output.rotation = rotation;
	return output;
}