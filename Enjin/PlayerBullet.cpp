#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
	safe_delete(model);
	for (int i = 0; i < PBULLET_MAX; i++)
	{
		safe_delete(bullet[i]);
	}
}

void PlayerBullet::Initialize(Input* input, Mouse* mouse, Rock* rock)
{
	this->input = input;
	this->mouse = mouse;
	this->rock = rock;

	model = Model::LoadFormOBJ("bullet");
	//’e
	for (int i = 0; i < PBULLET_MAX; i++)
	{
		bullet[i] = Object3d::Create();
		bullet[i]->SetModel(model);
		bullet[i]->SetPosition(position[i]);
		bullet[i]->SetRotation(rotation);
		bullet[i]->SetScale({ 0.7,0.7,0.7 });
	}
}

void PlayerBullet::Update()
{
	Move();
	for (int i = 0; i < PBULLET_MAX; i++)
	{
		bullet[i]->Update();
	}
}

void PlayerBullet::Draw()
{
	for (int i = 0; i < PBULLET_MAX; i++)
	{
		if (flag[i] == 1)
		{
			bullet[i]->Draw();
		}
	}
}

void PlayerBullet::Move()
{

	for (int i = 0; i < PBULLET_MAX; i++)
	{
		if (flag[i] == 1)
		{
			homingTime[i]++;
			if (homingTime[i] >= 5)
			{
				homingTime[i] = 0;
				homingCount[i] = 1;
			}
			//ƒJƒEƒ“ƒg‚ª0‚È‚çƒz[ƒ~ƒ“ƒO‚·‚é
			if (homingCount[i] == 0)
			{
				dx[i] = position[i].x - rock->GetPosition().x;//X‚Ì‹——£‚ÌŒvŽZ
				dy[i] = position[i].y - rock->GetPosition().y;//Y‚Ì‹——£‚ÌŒvŽZ
				dz[i] = position[i].z - rock->GetPosition().z;//Z‚Ì‹——£‚ÌŒvŽZ
				//ƒ‹[ƒg‚Ì’†‚ÌŒvŽZ
				da[i] = dx[i] * dx[i] + dy[i] * dy[i] + dz[i] * dz[i];
				//da = dx * dx + dy * dy;
				L[i] = sqrt(da[i]);
			}
			//’e‚ÌˆÚ“®
			position[i].x -= (dx[i] / L[i]) * speed;
			position[i].y -= (dy[i] / L[i]) * speed;
			position[i].z -= (dz[i] / L[i]) * speed;
		}

		if (position[i].z >= 100)
		{
			flag[i] = 0;
			homingCount[i] = 0;
		}
		bullet[i]->SetPosition(position[i]);
	}
}

void PlayerBullet::Create(XMFLOAT3 pos, int key)
{
	if (attackCT == 0)
	{
		if (input->PushKey(key) == true || mouse->PushMouseLeft() == true)
		{
			for (int i = 0; i < PBULLET_MAX; i++)
			{
				if (flag[i] == 0)
				{
					flag[i] = 1;
					position[i] = pos;
					attackCT = 1;
					break;
				}
			}
		}
	}
	else
	{
		attackCT += 1;
		if (attackCT >= 10)
		{
			attackCT = 0;
		}
	}

}


void PlayerBullet::PlusNumber()
{
	number += 1;
	if (number > PBULLET_MAX)
	{
		number = 0;
	}
}


void PlayerBullet::Hit()
{
	for (int i = 0; i < PBULLET_MAX; i++)
	{
		flag[i] = 0;
		homingCount[i] = 0;
		position[i].x = 1000;
	}
}