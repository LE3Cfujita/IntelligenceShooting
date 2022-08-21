#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
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
	bool ballToball(float pPos_x, float pPos_y, float pPos_z, float ePos_x, float ePos_y, float ePos_z, float r1, float r2);

	/// <summary>
	/// �l�p�`�Ǝl�p�`
	/// </summary>
	bool SquareToSquare(float pPos_x, float pPos_y, float ePos_x, float ePos_y, float width1, float height1, float width2, float height2);
};

