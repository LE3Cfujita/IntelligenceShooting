#include "EnemyBarrage.h"

EnemyBarrage::EnemyBarrage()
{
}

EnemyBarrage::~EnemyBarrage()
{
	safe_delete(model);
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		safe_delete(bullet[i]);
	}
}

void EnemyBarrage::Initialize()
{
	model = Model::LoadFormOBJ("enemyBullet");
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		position[i] = {100,100,100};
		bullet[i] = Object3d::Create();
		bullet[i]->SetModel(model);
		bullet[i]->SetPosition(position[i]);
		bullet[i]->SetRotation(rotation[i]);
		bullet[i]->SetScale({ 1,1,1 });
		bullet[i]->SetColor({ 255, 255, 0,0 });
	}
}

void EnemyBarrage::Update()
{
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		bullet[i]->Update();
	}
}

void EnemyBarrage::Draw()
{
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		if (flag[i] == 1)
		{
			bullet[i]->Draw();
		}
	}
}

void EnemyBarrage::Create(XMFLOAT3 ePos)
{
	if (coolCount == 0)
	{
		for (int i = 0; i < EBULLET_MAX; i++)
		{
			if (flag[i] == 0)
			{
				flag[i] = 1;
				homingTime[i] = 0;
				homingCount[i] = 0;
				position[i] = ePos;
				coolCount = 1;
				float move = 0.15;
				int directions = rand() % 3;
				if (directions == 0)
				{
					directionX[i] = move;
				}
				else if (directions == 1)
				{
					directionX[i] = -move;
				}
				else
				{
					directionX[i] = 0;
				}
				int directions2 = rand() % 3;
				if (directions2 == 0)
				{
					directionY[i] = move;
				}
				else if (directions2 == 1)
				{
					directionY[i] = -move;
				}
				else
				{
					directionY[i] = 0;
				}
				break;
			}
			bullet[i]->SetPosition(position[i]);
		}
	}
	else
	{
		coolTime++;
		if (coolTime < 7)return;
		coolTime = 0;
		coolCount = 0;
	}
}

void EnemyBarrage::Hit()
{
	flag[number] = 0;
	position[number].x = 100;
	position[number].y = 100;
	position[number].z = 100;
}

void EnemyBarrage::Move(XMFLOAT3 pPos)
{
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		if (flag[i] == 1)
		{
			homingTime[i]++;
			if (homingTime[i] >= 40)
			{
				homingTime[i] = 0;
				homingCount[i] = 1;
			}
			//カウントが0ならホーミングする
			if (homingCount[i] == 0)
			{
				dx[i] = pPos.x - position[i].x;//Xの距離の計算
				dy[i] = pPos.y - position[i].y;//Yの距離の計算
				dz[i] = pPos.z - position[i].z;//Zの距離の計算
				//ルートの中の計算
				da[i] = dx[i] * dx[i] + dy[i] * dy[i] + dz[i] * dz[i];
				L[i] = sqrt(da[i]);
			}
		}
		//弾の移動
		position[i].x += (dx[i] / L[i]) * speed + directionX[i];
		position[i].y += (dy[i] / L[i]) * speed + directionY[i];
		position[i].z += (dz[i] / L[i]) * speed;
		if (pPos.z - 10 > position[i].z)
		{
			flag[i] = 0;
			position[i].z = 100;
			homingTime[i] = 0;
			homingCount[i] = 0;
		}
		bullet[i]->SetPosition(position[i]);
	}
}


void EnemyBarrage::PlusNumber()
{
	number += 1;
	if (number > EBULLET_MAX)
	{
		number = 0;
	}
}
