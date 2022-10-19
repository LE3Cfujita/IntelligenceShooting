#include "OptionKey.h"

void OptionKey::Initialize(Input* input, Mouse* mouse)
{
	this->input = input;
	this->mouse = mouse;
	left = DIK_A;
	right = DIK_D;
	up = DIK_W;
	down = DIK_S;
	attack = DIK_SPACE;
	leftDecimal = 65;
	rightDecimal = 68;
	upDecimal = 87;
	downDecimal = 83;
	attackDecimal = 32;
}

void OptionKey::SettingKey()
{
	if (count != 0)
	{
		if (input->TriggerKey(DIK_A) == true)
		{
			if (count == 1)
			{
				up = DIK_A;
				upDecimal = 65;
			}
			else if (count == 2)
			{
				left = DIK_A;
				leftDecimal = 65;
			}
			else if (count == 3)
			{
				down = DIK_A;
				downDecimal = 65;
			}
			else if (count == 4)
			{
				right = DIK_A;
				rightDecimal = 65;
			}
			else if (count == 5)
			{
				attack = DIK_A;
				attackDecimal = 65;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_B) == true)
		{
			if (count == 1)
			{
				up = DIK_B;
				upDecimal = 66;
			}
			else if (count == 2)
			{
				left = DIK_B;
				leftDecimal = 66;
			}
			else if (count == 3)
			{
				down = DIK_B;
				downDecimal = 66;
			}
			else if (count == 4)
			{
				right = DIK_B;
				rightDecimal = 66;
			}
			else if (count == 5)
			{
				attack = DIK_B;
				attackDecimal = 66;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_C) == true)
		{
			if (count == 1)
			{
				up = DIK_C;
				upDecimal = 67;
			}
			else if (count == 2)
			{
				left = DIK_C;
				leftDecimal = 67;
			}
			else if (count == 3)
			{
				down = DIK_C;
				downDecimal = 67;
			}
			else if (count == 4)
			{
				right = DIK_C;
				rightDecimal = 67;
			}
			else if (count == 5)
			{
				attack = DIK_C;
				attackDecimal = 67;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_D) == true)
		{
			if (count == 1)
			{
				up = DIK_D;
				upDecimal = 68;
			}
			else if (count == 2)
			{
				left = DIK_D;
				leftDecimal = 68;
			}
			else if (count == 3)
			{
				down = DIK_D;
				downDecimal = 68;
			}
			else if (count == 4)
			{
				right = DIK_D;
				rightDecimal = 68;
			}
			else if (count == 5)
			{
				attack = DIK_D;
				attackDecimal = 68;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_E) == true)
		{
			if (count == 1)
			{
				up = DIK_E;
				upDecimal = 69;
			}
			else if (count == 2)
			{
				left = DIK_E;
				leftDecimal = 69;
			}
			else if (count == 3)
			{
				down = DIK_E;
				downDecimal = 69;
			}
			else if (count == 4)
			{
				right = DIK_E;
				rightDecimal = 69;
			}
			else if (count == 5)
			{
				attack = DIK_E;
				attackDecimal = 69;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_F) == true)
		{
			if (count == 1)
			{
				up = DIK_F;
				upDecimal = 70;
			}
			else if (count == 2)
			{
				left = DIK_F;
				leftDecimal = 70;
			}
			else if (count == 3)
			{
				down = DIK_F;
				downDecimal = 70;
			}
			else if (count == 4)
			{
				right = DIK_F;
				rightDecimal = 70;
			}
			else if (count == 5)
			{
				attack = DIK_F;
				attackDecimal = 70;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_G) == true)
		{
			if (count == 1)
			{
				up = DIK_G;
				upDecimal = 71;
			}
			else if (count == 2)
			{
				left = DIK_G;
				leftDecimal = 71;
			}
			else if (count == 3)
			{
				down = DIK_G;
				downDecimal = 71;
			}
			else if (count == 4)
			{
				right = DIK_G;
				rightDecimal = 71;
			}
			else if (count == 5)
			{
				attack = DIK_G;
				attackDecimal = 71;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_H) == true)
		{
			if (count == 1)
			{
				up = DIK_H;
				upDecimal = 72;
			}
			else if (count == 2)
			{
				left = DIK_H;
				leftDecimal = 72;
			}
			else if (count == 3)
			{
				down = DIK_H;
				downDecimal = 72;
			}
			else if (count == 4)
			{
				right = DIK_H;
				rightDecimal = 72;
			}
			else if (count == 5)
			{
				attack = DIK_H;
				attackDecimal = 72;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_I) == true)
		{
			if (count == 1)
			{
				up = DIK_I;
				upDecimal = 73;
			}
			else if (count == 2)
			{
				left = DIK_I;
				leftDecimal = 73;
			}
			else if (count == 3)
			{
				down = DIK_I;
				downDecimal = 73;
			}
			else if (count == 4)
			{
				right = DIK_I;
				rightDecimal = 73;
			}
			else if (count == 5)
			{
				attack = DIK_I;
				attackDecimal = 73;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_J) == true)
		{
			if (count == 1)
			{
				up = DIK_J;
				upDecimal = 74;
			}
			else if (count == 2)
			{
				left = DIK_J;
				leftDecimal = 74;
			}
			else if (count == 3)
			{
				down = DIK_J;
				downDecimal = 74;
			}
			else if (count == 4)
			{
				right = DIK_J;
				rightDecimal = 74;
			}
			else if (count == 5)
			{
				attack = DIK_J;
				attackDecimal = 74;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_K) == true)
		{
			if (count == 1)
			{
				up = DIK_K;
				upDecimal = 75;
			}
			else if (count == 2)
			{
				left = DIK_K;
				leftDecimal = 75;
			}
			else if (count == 3)
			{
				down = DIK_K;
				downDecimal = 75;
			}
			else if (count == 4)
			{
				right = DIK_K;
				rightDecimal = 75;
			}
			else if (count == 5)
			{
				attack = DIK_K;
				attackDecimal = 75;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_L) == true)
		{
			if (count == 1)
			{
				up = DIK_L;
				upDecimal = 76;
			}
			else if (count == 2)
			{
				left = DIK_L;
				leftDecimal = 76;
			}
			else if (count == 3)
			{
				down = DIK_L;
				downDecimal = 76;
			}
			else if (count == 4)
			{
				right = DIK_L;
				rightDecimal = 76;
			}
			else if (count == 5)
			{
				attack = DIK_L;
				attackDecimal = 76;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_M) == true)
		{
			if (count == 1)
			{
				up = DIK_M;
				upDecimal = 77;
			}
			else if (count == 2)
			{
				left = DIK_M;
				leftDecimal = 77;
			}
			else if (count == 3)
			{
				down = DIK_M;
				downDecimal = 77;
			}
			else if (count == 4)
			{
				right = DIK_M;
				rightDecimal = 77;
			}
			else if (count == 5)
			{
				attack = DIK_M;
				attackDecimal = 77;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_N) == true)
		{
			if (count == 1)
			{
				up = DIK_N;
				upDecimal = 78;
			}
			else if (count == 2)
			{
				left = DIK_N;
				leftDecimal = 78;
			}
			else if (count == 3)
			{
				down = DIK_N;
				downDecimal = 78;
			}
			else if (count == 4)
			{
				right = DIK_N;
				rightDecimal = 78;
			}
			else if (count == 5)
			{
				attack = DIK_N;
				attackDecimal = 78;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_O) == true)
		{
			if (count == 1)
			{
				up = DIK_O;
				upDecimal = 79;
			}
			else if (count == 2)
			{
				left = DIK_O;
				leftDecimal = 79;
			}
			else if (count == 3)
			{
				down = DIK_O;
				downDecimal = 79;
			}
			else if (count == 4)
			{
				right = DIK_O;
				rightDecimal = 79;
			}
			else if (count == 5)
			{
				attack = DIK_O;
				attackDecimal = 79;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_P) == true)
		{
			if (count == 1)
			{
				up = DIK_P;
				upDecimal = 80;
			}
			else if (count == 2)
			{
				left = DIK_P;
				leftDecimal = 80;
			}
			else if (count == 3)
			{
				down = DIK_P;
				downDecimal = 80;
			}
			else if (count == 4)
			{
				right = DIK_P;
				rightDecimal = 80;
			}
			else if (count == 5)
			{
				attack = DIK_P;
				attackDecimal = 80;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_Q) == true)
		{
			if (count == 1)
			{
				up = DIK_Q;
				upDecimal = 81;
			}
			else if (count == 2)
			{
				left = DIK_Q;
				leftDecimal = 81;
			}
			else if (count == 3)
			{
				down = DIK_Q;
				downDecimal = 81;
			}
			else if (count == 4)
			{
				right = DIK_Q;
				rightDecimal = 81;
			}
			else if (count == 5)
			{
				attack = DIK_Q;
				attackDecimal = 81;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_R) == true)
		{
			if (count == 1)
			{
				up = DIK_R;
				upDecimal = 82;
			}
			else if (count == 2)
			{
				left = DIK_R;
				leftDecimal = 82;
			}
			else if (count == 3)
			{
				down = DIK_R;
				downDecimal = 82;
			}
			else if (count == 4)
			{
				right = DIK_R;
				rightDecimal = 82;
			}
			else if (count == 5)
			{
				attack = DIK_R;
				attackDecimal = 82;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_S) == true)
		{
			if (count == 1)
			{
				up = DIK_S;
				upDecimal = 83;
			}
			else if (count == 2)
			{
				left = DIK_S;
				leftDecimal = 83;
			}
			else if (count == 3)
			{
				down = DIK_S;
				downDecimal = 83;
			}
			else if (count == 4)
			{
				right = DIK_S;
				rightDecimal = 83;
			}
			else if (count == 5)
			{
				attack = DIK_S;
				attackDecimal = 83;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_T) == true)
		{
			if (count == 1)
			{
				up = DIK_T;
				upDecimal = 84;
			}
			else if (count == 2)
			{
				left = DIK_T;
				leftDecimal = 84;
			}
			else if (count == 3)
			{
				down = DIK_T;
				downDecimal = 84;
			}
			else if (count == 4)
			{
				right = DIK_T;
				rightDecimal = 84;
			}
			else if (count == 5)
			{
				attack = DIK_T;
				attackDecimal = 84;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_U) == true)
		{
			if (count == 1)
			{
				up = DIK_U;
				upDecimal = 85;
			}
			else if (count == 2)
			{
				left = DIK_U;
				leftDecimal = 85;
			}
			else if (count == 3)
			{
				down = DIK_U;
				downDecimal = 85;
			}
			else if (count == 4)
			{
				right = DIK_U;
				rightDecimal = 85;
			}
			else if (count == 5)
			{
				attack = DIK_U;
				attackDecimal = 85;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_V) == true)
		{
			if (count == 1)
			{
				up = DIK_V;
				upDecimal = 86;
			}
			else if (count == 2)
			{
				left = DIK_V;
				leftDecimal = 86;
			}
			else if (count == 3)
			{
				down = DIK_V;
				downDecimal = 86;
			}
			else if (count == 4)
			{
				right = DIK_V;
				rightDecimal = 86;
			}
			else if (count == 5)
			{
				attack = DIK_V;
				attackDecimal = 86;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_W) == true)
		{
			if (count == 1)
			{
				up = DIK_W;
				upDecimal = 87;
			}
			else if (count == 2)
			{
				left = DIK_W;
				leftDecimal = 87;
			}
			else if (count == 3)
			{
				down = DIK_W;
				downDecimal = 87;
			}
			else if (count == 4)
			{
				right = DIK_W;
				rightDecimal = 87;
			}
			else if (count == 5)
			{
				attack = DIK_W;
				attackDecimal = 87;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_X) == true)
		{
			if (count == 1)
			{
				up = DIK_X;
				upDecimal = 88;
			}
			else if (count == 2)
			{
				left = DIK_X;
				leftDecimal = 88;
			}
			else if (count == 3)
			{
				down = DIK_X;
				downDecimal = 88;
			}
			else if (count == 4)
			{
				right = DIK_X;
				rightDecimal = 88;
			}
			else if (count == 5)
			{
				attack = DIK_X;
				attackDecimal = 88;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_Y) == true)
		{
			if (count == 1)
			{
				up = DIK_Y;
				upDecimal = 89;
			}
			else if (count == 2)
			{
				left = DIK_Y;
				leftDecimal = 89;
			}
			else if (count == 3)
			{
				down = DIK_Y;
				downDecimal = 89;
			}
			else if (count == 4)
			{
				right = DIK_Y;
				rightDecimal = 89;
			}
			else if (count == 5)
			{
				attack = DIK_Y;
				attackDecimal = 89;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_Z) == true)
		{
			if (count == 1)
			{
				up = DIK_Z;
				upDecimal = 90;
			}
			else if (count == 2)
			{
				left = DIK_Z;
				leftDecimal = 90;
			}
			else if (count == 3)
			{
				down = DIK_Z;
				downDecimal = 90;
			}
			else if (count == 4)
			{
				right = DIK_Z;
				rightDecimal = 90;
			}
			else if (count == 5)
			{
				attack = DIK_Z;
				attackDecimal = 90;
			}
			count = 0;
		}
		else if (input->TriggerKey(DIK_SPACE) == true)
		{
			if (count == 1)
			{
				up = DIK_SPACE;
				upDecimal = 32;
			}
			else if (count == 2)
			{
				left = DIK_SPACE;
				leftDecimal = 32;
			}
			else if (count == 3)
			{
				down = DIK_SPACE;
				downDecimal = 32;
			}
			else if (count == 4)
			{
				right = DIK_SPACE;
				rightDecimal = 32;
			}
			else if (count == 5)
			{
				attack = DIK_SPACE;
				attackDecimal = 32;
			}
			count = 0;
		}
	}
}

