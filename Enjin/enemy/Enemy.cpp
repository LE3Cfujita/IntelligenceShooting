#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	safe_delete(modelBoss);
	safe_delete(boss);
}

void Enemy::Initialize(Player* player)
{

	this->player = player;

	//OBJからモデルデータを読み込む
	modelBoss = Model::LoadFormOBJ("enemy");
	modelBullet = Model::LoadFormOBJ("bullet");
	//3Dオブジェクト生成
	boss = Object3d::Create();
	bullet = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	boss->SetModel(modelBoss);
	boss->SetPosition(enemy.position);
	boss->SetRotation(enemy.rotation);
	boss->SetScale({ 4,4,4 });

	bullet->SetModel(modelBullet);
	bullet->SetPosition(b.position);
	bullet->SetRotation(b.rotation);
	bullet->SetScale({ 0.7,0.7,0.7 });

	for (int i = 0; i < BULLET_MAX; i++)
	{
		bulletBarrage[i] = Object3d::Create();
		bulletBarrage[i]->SetModel(modelBullet);
		bulletBarrage[i]->SetPosition(barrage[i].position);
		bulletBarrage[i]->SetRotation(barrage[i].rotation);
		bulletBarrage[i]->SetScale({ 0.7,0.7,0.7 });
	}

}

void Enemy::Update()
{
	pPosition = player->GetPosition();

	if (pPosition.x < -5)
	{
		Attack1();
	}
	else if (pPosition.x > 5)
	{
		Attack2();
	}
	else
	{
		if (enemy.ct == 0)
		{
			Attack3();
		}
	}
	Attack1Move();
	Attack2Move();
	Attack3Move();
	boss->Update();
	bullet->Update();
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bulletBarrage[i]->Update();
	}
}

void Enemy::Draw()
{
	boss->Draw();
	if (b.flag == 1)
	{
		bullet->Draw();
	}
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (barrage[i].flag == 1)
		{
			bulletBarrage[i]->Draw();
		}
	}
}

void Enemy::Attack1()
{
	if (enemy.position.y <= 15)
	{
		if (enemy.attackFlag == 0 && enemy.attackFlag3 == 0 && b.flag == 0)
		{
			enemy.attackFlag = 1;
			b.position = enemy.position;
			homingCount = 0;
			b.flag = 1;
		}
	}


	bullet->SetPosition(b.position);

}

void Enemy::Attack1Move()
{
	if (enemy.attackFlag == 1)
	{
		homingTime++;
		if (homingTime >= 20)
		{
			homingTime = 0;
			homingCount = 1;
		}
		//カウントが0ならホーミングする
		if (homingCount == 0)
		{
			b.dx = pPosition.x - b.position.x;//Xの距離の計算
			b.dy = pPosition.y - b.position.y;//Yの距離の計算
			b.dz = pPosition.z - b.position.z;//Zの距離の計算
			//ルートの中の計算
			b.da = b.dx * b.dx + b.dy * b.dy + b.dz * b.dz;
			//da = dx * dx + dy * dy;
			b.L = sqrt(b.da);
		}
		//弾の移動
		b.position.x += (b.dx / b.L) * b.speed;
		b.position.y += (b.dy / b.L) * b.speed;
		b.position.z += (b.dz / b.L) * b.speed;



	}
	if (pPosition.z - 10 > b.position.z)
	{
		enemy.attackFlag = 0;
		b.flag = 0;
		b.position.z = 100;
	}
	bullet->SetPosition(b.position);
}

void Enemy::Attack2()
{
	if (enemy.position.y <= 15)
	{
		if (enemy.attackFlag2 == 0 && enemy.attackFlag3 == 0)
		{
			enemy.attackFlag2 = 1;
		}
	}
	if (enemy.attackFlag2 == 1)
	{

		if (enemy.barrageTime == 0)
		{
			enemy.barrageTime = 1;
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (barrage[i].flag == 0)
				{
					barrage[i].flag = 1;
					barrage[i].position = enemy.position;
					float move = 0.1;
					barrage[i].direction.x = (rand() % 10 + 1) * -move;

					int direction = rand() % 2;
					if (direction == 1)
					{
						move = -0.05;
					}
					barrage[i].direction.y = (rand() % 10) * move;

					break;
				}
			}
		}
		else
		{
			enemy.barrageTime++;
			if (enemy.barrageTime >= 2)
			{
				enemy.barrageTime = 0;
			}
		}
	}
}

void Enemy::Attack2Move()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (barrage[i].flag == 1)
		{
			barrage[i].position.x -= barrage[i].direction.x;
			barrage[i].position.y -= barrage[i].direction.y;
			barrage[i].position.z -= barrage[i].speed;
		}
		if (pPosition.z - 10 >= barrage[i].position.z)
		{
			enemy.attackFlag2 = 0;
			barrage[i].flag = 0;
			barrage[i].position.z = 100;
		}
		bulletBarrage[i]->SetPosition(barrage[i].position);

	}

}

void Enemy::Attack3()
{
	if (enemy.attackFlag3 == 0)
	{
		enemy.attackFlag3 = 1;
		enemy.ct = 60;
	}
}

void Enemy::Attack3Move()
{

	if (enemy.attackFlag3 == 1)
	{
		if (enemy.rotCount == 0)
		{
			enemy.rotation.z -= 8;
			enemy.position.z += 5;

			if (enemy.rotation.z <= -300)
			{
				enemy.rotCount = 1;
			}
		}
		if (enemy.rotCount == 1)
		{
			enemy.rotation.z += 16;
			enemy.position.z -= 10;
		}
	}
	if (enemy.ct > 0 && enemy.position.z == 100)
	{

		enemy.ct--;
		if (enemy.position.y > 0)
		{
			enemy.position.y -= 3;
		}
	}
	if (pPosition.z - 30 >= enemy.position.z)
	{
		enemy.position = { 0,210,100 };
		enemy.rotation = { 0,180,0 };
		enemy.ct = 180;
		enemy.rotCount = 0;
		enemy.attackFlag3 = 0;
	}

	boss->SetRotation(enemy.rotation);
	boss->SetPosition(enemy.position);
}
