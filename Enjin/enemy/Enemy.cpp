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

}

void Enemy::Update()
{
	pPosition = player->GetPosition();
	if (pPosition.x <= -5)
	{
		Attack1();
	}
	Attack1Move();
	boss->Update();
	bullet->Update();
}

void Enemy::Draw()
{
	boss->Draw();
	bullet->Draw();
}

void Enemy::Attack1()
{
	if (b.flag == 0)
	{
		enemy.attackFlag = 1;
		b.position = enemy.position;
		homingCount = 0;
		b.flag = 1;
	}


	bullet->SetPosition(b.position);

}

void Enemy::Attack1Move()
{
	if (enemy.attackFlag == 1)
	{
		homingTime++;
		if (homingTime >= 30)
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

		if (pPosition.z + -10 >= b.position.z)
		{
			enemy.attackFlag = 0;
			b.flag = 0;

		}

	}

	bullet->SetPosition(b.position);
}
