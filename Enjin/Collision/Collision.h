#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
using namespace DirectX;
class Collision
{
public:
	/// <summary>
/// �~�Ǝl�p�`
/// </summary>
	bool CircleToSquare(float pPos_x, float pPos_y, float ePos_x, float ePos_y, float r, float width, float height);

	/// <summary>
	/// ���Ƌ�
	/// </summary>
	bool ballToball(XMFLOAT3 pPos,XMFLOAT3 ePos, float r1, float r2);

	/// <summary>
	/// �l�p�`�Ǝl�p�`
	/// </summary>
	bool SquareToSquare(float pPos_x, float pPos_y, float ePos_x, float ePos_y, float width1, float height1, float width2, float height2);
};

