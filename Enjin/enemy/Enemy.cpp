#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	safe_delete(modelBoss);
	safe_delete(boss);

}

void Enemy::Initialize()
{

	position = { 0,0,100 };
	rotation = { 0,180,0 };

	objectMember = OBJECTMEMBER::ENEMY;
	//OBJからモデルデータを読み込む
	modelBoss = Model::LoadFormOBJ("enemy");
	//3Dオブジェクト生成
	boss = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	boss->SetModel(modelBoss);
	boss->SetPosition(position);
	boss->SetRotation(rotation);
	boss->SetScale({ 4,4,4 });



	directionX = rand() % 2;
	directionY = rand() % 2;
}

void Enemy::Update()
{
	if (attackFlag3 == 0)
	{
		Move();
	}
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::PLAYER)
		{
			XMFLOAT3 pos = gameobject->GetPosition();

			//Attack1();
			if (pos.x < -5 || pos.x > 5)
			{
				Attack2();
			}
			else
			{
				if (ct == 0)
				{
					//Attack3();
				}
			}
		}
	}
	Attack3Move();
}

void Enemy::Draw()
{
	boss->Update();
	boss->Draw();
}

void Enemy::Move()
{
	MoveLimit();

	if (!(directionX == 0) || !(directionY == 0))return;

	if (aim.getTime == 0)
	{
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::ROCK)return;
			{
				aim.rPosition = gameobject->GetPosition();
			}
		}
		aim.getTime = 1;
		speed = 1;

		//照準との距離を計算して逃げるような動きを作る
		aim.dx = position.x - aim.rPosition.x;
		aim.dy = position.y - aim.rPosition.y;
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
	speed -= 0.02;
	if (aim.dx < 0)
	{
		position.x -= speed;
	}
	else
	{
		position.x += speed;
	}
	if (aim.dy < 0)
	{
		position.y -= speed;
	}
	else
	{
		position.y += speed;
	}
	boss->SetPosition(position);
}

void Enemy::MoveLimit()
{
	if (position.x > 90)
	{
		directionX = 1;
		speed = 2;
	}
	if (position.x < -90)
	{
		directionX = 2;
		speed = 2;
	}
	if (position.y > 60)
	{
		directionY = 1;
		speed = 2;
	}
	if (position.y < -55)
	{
		directionY = 2;
		speed = 2;
	}

	if (directionX == 1)
	{
		position.x -= speed;
		speed -= 0.02;
	}
	if (directionX == 2)
	{
		position.x += speed;
		speed -= 0.02;
	}
	if (directionY == 1)
	{
		position.y -= speed;
		if (position.y < 60)
		{
			speed -= 0.02;
		}
	}
	if (directionY == 2)
	{
		position.y += speed;
		speed -= 0.02;
	}

	if (speed <= 0)
	{
		directionX = 0;
		directionY = 0;
		speed = 1;
	}
	boss->SetPosition(position);
}

void Enemy::Attack1()
{
	if (position.y <= 60 && attackFlag == 0 && attackFlag3 == 0)
	{
		EnemyBullet* bullet = new EnemyBullet();
		bullet->BaseInitialize(input, audio, mouse, referenceGameObjects);
		bullet->Initialize();
		addGameObjects.push_back(bullet);
		bullet->Create(position);
		attackFlag = 1;
	}
}



void Enemy::Attack2()
{
	if (position.y <= 60 && attackFlag3 == 0)
	{
		if (coolCount == 0)
		{
			EnemyBarrage* barrage = new EnemyBarrage();
			barrage->BaseInitialize(input, audio, mouse, referenceGameObjects);
			barrage->Initialize();
			addGameObjects.push_back(barrage);
			barrage->Create(position);
			attackFlag2 = 1;
			coolCount = 1;
		}
		else
		{
			coolTime++;
			if (coolTime < 5)return;
			coolTime = 0;
			coolCount = 0;
		}
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
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::PLAYER)return;
		XMFLOAT3 pos = gameobject->GetPosition();
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
				dx = position.x - pos.x;//Xの距離の計算
				dy = position.y - pos.y;//Yの距離の計算
				dz = position.z - pos.z;//Zの距離の計算
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
		if (pos.z - 30 >= position.z)
		{
			position = { 0,120,100 };
			rotation = { 0,180,0 };
			ct = 300;
			rotCount = 0;
			attackFlag3 = 0;
			homingCount = 0;
			homingTime = 0;
			rushCount = 0;
			speed = 1;
		}
	}
	boss->SetRotation(rotation);
	boss->SetPosition(position);
}

void Enemy::BHit()
{
	attackFlag = 0;
	//bullet->Hit();
}

void Enemy::BarrageHit()
{
	attackFlag2 = 0;
	//barrage->Hit();
}

void Enemy::RushHit()
{
	rushCount = 1;
}

void Enemy::PHit()
{
	HP -= 1;
}