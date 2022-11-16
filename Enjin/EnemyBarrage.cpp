#include "EnemyBarrage.h"

EnemyBarrage::EnemyBarrage()
{
}

EnemyBarrage::~EnemyBarrage()
{
	safe_delete(model);
	safe_delete(bullet);
}

void EnemyBarrage::Initialize()
{
	model = Model::LoadFormOBJ("enemyBullet");

	objectMember = OBJECTMEMBER::ENEMYBARRAGE;

	position = { 100,100,100 };
	bullet = Object3d::Create();
	bullet->SetModel(model);
	bullet->SetPosition(position);
	bullet->SetRotation(rotation);
	bullet->SetScale({ 1,1,1 });
	bullet->SetColor({ 255, 255, 0,0 });
}

void EnemyBarrage::Update()
{
	Move();
}

void EnemyBarrage::Draw()
{
	bullet->Update();
	bullet->Draw();
}

void EnemyBarrage::Create(XMFLOAT3 ePos)
{
	if (coolCount == 0)
	{
		if (deathFlag == true)
		{
			deathFlag = false;
			homingTime = 0;
			homingCount = 0;
			position = ePos;
			coolCount = 1;
			float move = 0.15;
			int directions = rand() % 3;
			if (directions == 0)
			{
				directionX = move;
			}
			else if (directions == 1)
			{
				directionX = -move;
			}
			else
			{
				directionX = 0;
			}
			int directions2 = rand() % 3;
			if (directions2 == 0)
			{
				directionY = move;
			}
			else if (directions2 == 1)
			{
				directionY = -move;
			}
			else
			{
				directionY = 0;
			}
		}
		bullet->SetPosition(position);
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
	deathFlag = true;
	position.x = 100;
	position.y = 100;
	position.z = 100;
}

void EnemyBarrage::Move()
{
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::PLAYER)
		{
			XMFLOAT3 pos = gameobject->GetPosition();
			if (deathFlag == false)
			{
				homingTime++;
				if (homingTime >= 40)
				{
					homingTime = 0;
					homingCount = 1;
				}
				//カウントが0ならホーミングする
				if (homingCount == 0)
				{
					dx = pos.x - position.x;//Xの距離の計算
					dy = pos.y - position.y;//Yの距離の計算
					dz = pos.z - position.z;//Zの距離の計算
					//ルートの中の計算
					da = dx * dx + dy * dy + dz * dz;
					L = sqrt(da);
				}
			}
			//弾の移動
			position.x += (dx / L) * speed + directionX;
			position.y += (dy / L) * speed + directionY;
			position.z += (dz / L) * speed;
			if (pos.z - 10 > position.z)
			{
				deathFlag = true;
				position.z = 100;
				homingTime = 0;
				homingCount = 0;
			}
		}
	}
	bullet->SetPosition(position);
}
