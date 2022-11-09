#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	safe_delete(modelBoss);
	safe_delete(boss);

}

void Enemy::Initialize(Player* player, Rock* rock, EnemyBullet* bullet, EnemyBarrage* barrage)
{

	this->player = player;
	this->rock = rock;
	this->bullet = bullet;
	this->barrage = barrage;
	//OBJからモデルデータを読み込む
	modelBoss = Model::LoadFormOBJ("enemy");
	//3Dオブジェクト生成
	boss = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	boss->SetModel(modelBoss);
	boss->SetPosition(enemy.position);
	boss->SetRotation(enemy.rotation);
	boss->SetScale({ 4,4,4 });



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
	barrage->Move(pPosition);
	Attack3Move();
	boss->Update();
}

void Enemy::Draw()
{
	boss->Draw();
}

void Enemy::Move()
{
	MoveLimit();

	if (!(enemy.directionX == 0) || !(enemy.directionY == 0))return;
	if (aim.getTime == 0)
	{
		aim.rPosition = rock->GetPosition();
		aim.getTime = 1;
		enemy.speed = 1;

		//照準との距離を計算して逃げるような動きを作る
		aim.dx = enemy.position.x - aim.rPosition.x;
		aim.dy = enemy.position.y - aim.rPosition.y;
		aim.da = aim.dx * aim.dx + aim.dy + aim.dy;
		aim.L = sqrt(aim.da);
	}
	else
	{
		aim.getTime++;
		if (aim.getTime >= 50)
		{
			aim.getTime = 0;
		}
	}
	if (aim.L >= 30)return;
	enemy.speed -= 0.02;
	if (aim.dx < 0)
	{
		enemy.position.x -= enemy.speed;
	}
	else
	{
		enemy.position.x += enemy.speed;
	}
	if (aim.dy < 0)
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
		if (enemy.attackFlag == 0 && enemy.attackFlag3 == 0 && bullet->GetFlag() == 0)
		{
			bullet->Create(enemy.position);
			enemy.attackFlag = 1;
		}
	}
}

void Enemy::Attack1Move()
{
	if (enemy.attackFlag == 1)
	{
		bullet->Move(pPosition);
	}

	if (pPosition.z - 10 > bullet->GetPos().z)
	{
		enemy.attackFlag = 0;
		bullet->SetFlag(0);
		bullet->SetPos({ 100,100,100 });
	}
}


void Enemy::Attack2()
{
	if (enemy.position.y <= 60 && enemy.attackFlag3 == 0)
	{
		barrage->Create(enemy.position);
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
	bullet->Hit();
}

void Enemy::BarrageHit()
{
	enemy.attackFlag2 = 0;
	barrage->Hit();
}

void Enemy::RushHit()
{
	enemy.rushCount = 1;
}

void Enemy::PHit()
{
	enemy.HP -= 1;
}