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
	modelBullet = Model::LoadFormOBJ("enemyBullet");
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

	for (int i = 0; i < EBULLET_MAX; i++)
	{
		bulletBarrage[i] = Object3d::Create();
		bulletBarrage[i]->SetModel(modelBullet);
		bulletBarrage[i]->SetPosition(barrage[i].position);
		bulletBarrage[i]->SetRotation(barrage[i].rotation);
		bulletBarrage[i]->SetScale({ 1,1,1 });
		bulletBarrage[i]->SetColor({ 255, 255, 0,0 });
	}
	enemy.directionX = rand() % 2;
	enemy.directionY = rand() % 2;
}

void Enemy::Update()
{
	if (enemy.attackFlag3 == 0)
	{
		Move();
	}
	pPosition = player->GetPosition();

	Attack1();
	if (pPosition.x < -5 || pPosition.x > 5)
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
	for (int i = 0; i < EBULLET_MAX; i++)
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
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		if (barrage[i].flag == 1)
		{
			bulletBarrage[i]->Draw();
		}
	}
}

void Enemy::Move()
{
	MoveLimit();

	if (!(enemy.directionX == 0) || !(enemy.directionY == 0))return;
	if (rock.getTime == 0)
	{
		rock.rPosition = player->GetAimPosition();
		rock.getTime = 1;
		enemy.speed = 1;

		//照準との距離を計算して逃げるような動きを作る
		rock.dx = enemy.position.x - rock.rPosition.x;
		rock.dy = enemy.position.y - rock.rPosition.y;
		rock.da = rock.dx * rock.dx + rock.dy + rock.dy;
		rock.L = sqrt(rock.da);
	}
	else
	{
		rock.getTime++;
		if (rock.getTime >= 50)
		{
			rock.getTime = 0;
		}
	}
	if (rock.L >= 30)return;
	enemy.speed -= 0.02;
	if (rock.dx < 0)
	{
		enemy.position.x -= enemy.speed;
	}
	else
	{
		enemy.position.x += enemy.speed;
	}
	if (rock.dy < 0)
	{
		enemy.position.y -= enemy.speed;
	}
	else
	{
		enemy.position.y += enemy.speed;
	}
	boss->SetPosition(enemy.position);
}

void Enemy::MoveLimit()
{
	if (enemy.position.x > 90)
	{
		enemy.directionX = 1;
		enemy.speed = 2;
	}
	if (enemy.position.x < -90)
	{
		enemy.directionX = 2;
		enemy.speed = 2;
	}
	if (enemy.position.y > 60)
	{
		enemy.directionY = 1;
		enemy.speed = 2;
	}
	if (enemy.position.y < -55)
	{
		enemy.directionY = 2;
		enemy.speed = 2;
	}

	if (enemy.directionX == 1)
	{
		enemy.position.x -= enemy.speed;
		enemy.speed -= 0.02;
	}
	if (enemy.directionX == 2)
	{
		enemy.position.x += enemy.speed;
		enemy.speed -= 0.02;
	}
	if (enemy.directionY == 1)
	{
		enemy.position.y -= enemy.speed;
		if (enemy.position.y < 60)
		{
			enemy.speed -= 0.02;
		}
	}
	if (enemy.directionY == 2)
	{
		enemy.position.y += enemy.speed;
		enemy.speed -= 0.02;
	}

	if (enemy.speed <= 0)
	{
		enemy.directionX = 0;
		enemy.directionY = 0;
		enemy.speed = 1;
	}
	boss->SetPosition(enemy.position);
}

void Enemy::Attack1()
{
	if (enemy.position.y <= 60)
	{
		if (enemy.attackFlag == 0 && enemy.attackFlag3 == 0 && b.flag == 0)
		{
			enemy.attackFlag = 1;
			b.position = enemy.position;
			b.homingCount = 0;
			b.flag = 1;
		}
	}


	bullet->SetPosition(b.position);

}

void Enemy::Attack1Move()
{
	if (enemy.attackFlag == 1)
	{
		b.homingTime++;
		if (b.homingTime >= 40)
		{
			b.homingTime = 0;
			b.homingCount = 1;
		}
		//カウントが0ならホーミングする
		if (b.homingCount == 0)
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
		enemy.attackFlag = 0;
		b.flag = 0;
		b.position.z = 100;
	}
	bullet->SetPosition(b.position);
}


void Enemy::Attack2()
{
	if (enemy.position.y <= 60)
	{
		if (coolCount == 0)
		{
			for (int i = 0; i < EBULLET_MAX; i++)
			{
				if (enemy.attackFlag3 == 0 && barrage[i].flag == 0)
				{
					barrage[i].flag = 1;
					barrage[i].homingTime = 0;
					barrage[i].homingCount = 0;
					barrage[i].position = enemy.position;
					coolCount = 1;
					float move = 0.15;
					int directions = rand() % 3;
					if (directions == 0)
					{
						barrage[i].directionX = move;
					}
					else if (directions == 1)
					{
						barrage[i].directionX = -move;
					}
					else
					{
						barrage[i].directionX = 0;
					}
					int directions2 = rand() % 3;
					if (directions2 == 0)
					{
						barrage[i].directionY = move;
					}
					else if (directions2 == 1)
					{
						barrage[i].directionY = -move;
					}
					else
					{
						barrage[i].directionY = 0;
					}
					break;
				}
				bulletBarrage[i]->SetPosition(barrage[i].position);
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
}
void Enemy::Attack2Move()
{
	for (int i = 0; i < EBULLET_MAX; i++)
	{
		if (barrage[i].flag == 1)
		{
			barrage[i].homingTime++;
			if (barrage[i].homingTime >= 40)
			{
				barrage[i].homingTime = 0;
				barrage[i].homingCount = 1;
			}
			//カウントが0ならホーミングする
			if (barrage[i].homingCount == 0)
			{
				barrage[i].dx = pPosition.x - barrage[i].position.x;//Xの距離の計算
				barrage[i].dy = pPosition.y - barrage[i].position.y;//Yの距離の計算
				barrage[i].dz = pPosition.z - barrage[i].position.z;//Zの距離の計算
				//ルートの中の計算
				barrage[i].da = barrage[i].dx * barrage[i].dx + barrage[i].dy * barrage[i].dy + barrage[i].dz * barrage[i].dz;
				barrage[i].L = sqrt(barrage[i].da);
			}
		}
		//弾の移動
		barrage[i].position.x += (barrage[i].dx / barrage[i].L) * barrage[i].speed + barrage[i].directionX;
		barrage[i].position.y += (barrage[i].dy / barrage[i].L) * barrage[i].speed + barrage[i].directionY;
		barrage[i].position.z += (barrage[i].dz / barrage[i].L) * barrage[i].speed;
		if (pPosition.z - 10 > barrage[i].position.z)
		{
			barrage[i].flag = 0;
			barrage[i].position.z = 100;
			barrage[i].homingTime = 0;
			barrage[i].homingCount = 0;
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
		enemy.homingTime++;
		if (enemy.homingTime >= 60)
		{
			enemy.homingTime = 0;
			enemy.homingCount = 1;
		}
		//カウントが0ならホーミングする
		if (enemy.homingCount == 0)
		{
			enemy.dx = enemy.position.x - pPosition.x;//Xの距離の計算
			enemy.dy = enemy.position.y - pPosition.y;//Yの距離の計算
			enemy.dz = enemy.position.z - pPosition.z;//Zの距離の計算
			//ルートの中の計算
			enemy.da = enemy.dx * enemy.dx + enemy.dy * enemy.dy + enemy.dz * enemy.dz;
			enemy.L = sqrt(enemy.da);
		}


		if (enemy.rotCount == 0)
		{
			enemy.rotation.z -= 8;
			enemy.position.x += (enemy.dx / enemy.L) * 5;
			enemy.position.y += (enemy.dy / enemy.L) * 5;
			enemy.position.z += (enemy.dz / enemy.L) * 5;

			if (enemy.rotation.z <= -300)
			{
				enemy.rotCount = 1;
				enemy.homingCount = 0;
			}
		}
		if (enemy.rotCount == 1)
		{
			enemy.rotation.z += 16;
			enemy.position.x -= (enemy.dx / enemy.L) * 10;
			enemy.position.y -= (enemy.dy / enemy.L) * 10;
			enemy.position.z -= (enemy.dz / enemy.L) * 10;
		}
	}
	if (enemy.ct > 0 && enemy.position.z == 100)
	{

		enemy.ct--;
	}
	if (pPosition.z - 30 >= enemy.position.z)
	{
		enemy.position = { 0,120,100 };
		enemy.rotation = { 0,180,0 };
		enemy.ct = 300;
		enemy.rotCount = 0;
		enemy.attackFlag3 = 0;
		enemy.homingCount = 0;
		enemy.homingTime = 0;
		enemy.rushCount = 0;
		enemy.speed = 1;
	}

	boss->SetRotation(enemy.rotation);
	boss->SetPosition(enemy.position);
}

void Enemy::BHit()
{
	enemy.attackFlag = 0;
	b.flag = 0;
	b.position.z = 100;
	bullet->SetPosition(b.position);
}

void Enemy::BarrageHit()
{
	enemy.attackFlag2 = 0;
	barrage[barrageNumber].flag = 0;
	barrage[barrageNumber].position.x = 100;
	barrage[barrageNumber].position.y = 100;
	barrage[barrageNumber].position.z = 100;
}

void Enemy::RushHit()
{
	enemy.rushCount = 1;
}

void Enemy::PHit()
{
	enemy.HP -= 1;
}

void Enemy::PlusNumber()
{
	barrageNumber += 1;
	if (barrageNumber > EBULLET_MAX)
	{
		barrageNumber = 0;
	}
}
