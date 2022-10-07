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

	/*this->player = player;
	this->aim = aim;*/

	//OBJからモデルデータを読み込む
	modelBoss = Model::LoadFormOBJ("enemy");
	modelBullet = Model::LoadFormOBJ("enemyBullet");
	//3Dオブジェクト生成
	boss = Object3d::Create();
	bullet = Object3d::Create();

	BaseInitialize(input, audio);
	position = { 0,0,100 };
	rotation = { 0,180,0 };
	scale = { 3,3,3 };


	//オブジェクトにモデルを紐付ける
	boss->SetModel(modelBoss);
	boss->SetPosition(position);
	boss->SetRotation(rotation);
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
		bulletBarrage[i]->SetScale({ 1,1,1 });
	}
	directionX = rand() % 2;
	directionY = rand() % 2;
}

void Enemy::Update()
{
	if (attackFlag3 == 0)
	{
		Move();
	}
	pPosition = player->GetPosition();

	if (position.y <= 60)
	{
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
			if (ct == 0)
			{
				Attack3();
			}
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

void Enemy::Move()
{

	rock.rPosition = aim->GetPosition();

	//照準との距離を計算して逃げるような動きを作る
	rock.dx = position.x - rock.rPosition.x;
	rock.dy = position.y - rock.rPosition.y;
	rock.da = rock.dx * rock.dx + rock.dy + rock.dy;
	rock.L = sqrt(rock.da);

	if (directionX == 0)
	{
		position.x += speed;
	}
	if (directionX == 1)
	{
		position.x -= speed;
	}
	if (directionY == 0)
	{
		position.y += speed;
	}
	if (directionY == 1)
	{
		position.y -= speed;
	}

	if (rock.directionCount == 1)
	{
		rock.directionTime++;
		if (rock.directionTime > 10)
		{
			rock.directionTime = 0;
			rock.directionCount = 0;
		}
	}

	if (rock.L <= 8 && rock.directionCount == 0)
	{
		if (position.x < 80 && position.x <= rock.rPosition.x)
		{
			directionX = 0;
			rock.directionCount = 1;
		}
		else if (position.x > -80 && position.x >= rock.rPosition.x)
		{
			directionX = 1;
			rock.directionCount = 1;
		}
		if (position.y < 60 && position.y >= rock.rPosition.y);
		{
			directionY = 0;
			rock.directionCount = 1;
		}
		if (position.y > -55 && position.y <= rock.rPosition.y)
		{
			directionY = 1;
			rock.directionCount = 1;
		}
	}
	else
	{
		if (position.x >= 80)
		{
			if (directionX == 0)
			{
				directionX = 1;
			}
		}
		if (position.x <= -80)
		{
			if (directionX == 1)
			{
				directionX = 0;
			}
		}
		if (position.y >= 60)
		{
			if (directionY == 0)
			{
				directionY = 1;
			}
		}
		if (position.y <= -55)
		{
			if (directionY == 1)
			{
				directionY = 0;
			}
		}
	}
	boss->SetPosition(position);
}

void Enemy::Attack1()
{
	if (position.y <= 60)
	{
		if (attackFlag == 0 && attackFlag3 == 0 && b.flag == 0)
		{
			attackFlag = 1;
			b.position = position;
			homingCount = 0;
			b.flag = 1;
		}
	}


	bullet->SetPosition(b.position);

}

void Enemy::Attack1Move()
{
	if (attackFlag == 1)
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
			b.L = sqrt(b.da);
		}
		//弾の移動
		b.position.x += (b.dx / b.L) * b.speed;
		b.position.y += (b.dy / b.L) * b.speed;
		b.position.z += (b.dz / b.L) * b.speed;
	}

	if (pPosition.z - 10 > b.position.z)
	{
		attackFlag = 0;
		b.flag = 0;
		b.position.z = 100;
	}
	bullet->SetPosition(b.position);
}

void Enemy::Attack2()
{
	if (position.y <= 60)
	{
		if (attackFlag2 == 0 && attackFlag3 == 0)
		{
			attackFlag2 = 1;
		}
	}
	if (attackFlag2 == 1)
	{

		if (barrageTime == 0)
		{
			barrageTime = 1;
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (barrage[i].flag == 0)
				{
					barrage[i].flag = 1;
					barrage[i].position = position;
					float move = 0.2;
					int directions = rand() % 2;
					if (directions == 0)
					{
						barrage[i].direction.x = (rand() % 10 + 1) * move;
					}
					else
					{
						barrage[i].direction.x = (rand() % 10 + 1) * -move;
					}
					int direction = rand() % 2;
					if (direction == 1)
					{
						move = -0.07;
					}
					barrage[i].direction.y = (rand() % 10) * move;

					break;
				}
			}
		}
		else
		{
			barrageTime++;
			if (barrageTime >= 2)
			{
				barrageTime = 0;
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
			attackFlag2 = 0;
			barrage[i].flag = 0;
			barrage[i].position.z = 100;
		}
		bulletBarrage[i]->SetPosition(barrage[i].position);

	}

}

void Enemy::Attack3()
{
	if (attackFlag3 == 0)
	{
		attackFlag3 = 1;
		ct = 60;
	}
}

void Enemy::Attack3Move()
{

	if (attackFlag3 == 1)
	{
		homingTime++;
		if (homingTime >= 60)
		{
			homingTime = 0;
			homingCount = 1;
		}
		//カウントが0ならホーミングする
		if (homingCount == 0)
		{
			dx = position.x - pPosition.x;//Xの距離の計算
			dy = position.y - pPosition.y;//Yの距離の計算
			dz = position.z - pPosition.z;//Zの距離の計算
			//ルートの中の計算
			da = dx * dx + dy * dy + dz * dz;
			L = sqrt(da);
		}


		if (rotCount == 0)
		{
			rotation.z -= 8;
			position.x += (dx / L) * 5;
			position.y += (dy / L) * 5;
			position.z += (dz / L) * 5;

			if (rotation.z <= -300)
			{
				rotCount = 1;
				homingCount = 0;
			}
		}
		if (rotCount == 1)
		{
			rotation.z += 16;
			position.x -= (dx / L) * 10;
			position.y -= (dy / L) * 10;
			position.z -= (dz / L) * 10;
		}
	}
	if (ct > 0 && position.z == 100)
	{
		ct--;
	}
	if (pPosition.z - 30 >= position.z)
	{
		position = { 0,120,100 };
		rotation = { 0,180,0 };
		ct = 300;
		rotCount = 0;
		attackFlag3 = 0;
		homingCount = 0;
		homingTime = 0;
		rushCount = 0;
	}

	boss->SetRotation(rotation);
	boss->SetPosition(position);
}

void Enemy::BHit()
{
	attackFlag = 0;
	b.flag = 0;
	b.position.z = 100;
	bullet->SetPosition(b.position);
}

void Enemy::BarrageHit()
{
	attackFlag2 = 0;
	barrage[barrageNumber].flag = 0;
	barrage[barrageNumber].position.x = 100;
	barrage[barrageNumber].position.y = 100;
	barrage[barrageNumber].position.z = 100;
}

void Enemy::RushHit()
{
	rushCount = 1;
}

void Enemy::PHit()
{
	HP -= 1;
}

void Enemy::PlusNumber()
{
	barrageNumber += 1;
	if (barrageNumber > BULLET_MAX)
	{
		barrageNumber = 0;
	}
}
