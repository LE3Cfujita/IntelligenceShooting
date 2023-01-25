#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	safe_delete(boss);
}

void Enemy::Initialize()
{

	position = { 0,100,100 };
	rotation = { 0,0,0 };
	radius = 10;
	HP = maxHP;
	objectMember = OBJECTMEMBER::ENEMY;
	//OBJからモデルデータを読み込む
	modelBoss = Model::CreateModel(5);
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
	if (moveFlag == false)
	{
		if (position.y <= 60)
		{
			moveFlag = true;
		}
	}
	if (attackFlag3 == 0 && attack == true)
	{
		Move();
	}
	for (GameObject* gameobject : referenceGameObjects)
	{
		XMFLOAT3 pos;
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::PLAYER)continue;
		pos = gameobject->GetPosition();
		if (position.y <= 60)
		{
			if (attack == true)
			{
				if (attackCount == 0)
				{
					Attack1();
				}
				else
				{
					Attack4();
				}
				if (pos.x < -7 || pos.x > 7)
				{
					Attack2();
				}
				else
				{
					if (ct == 0)
					{
						Attack3();
					}
					if (ct > 0 && position.z == 100)
					{
						ct--;
					}
				}

			}

			if (attackFlag3 == 0 && HP == maxHP / 2 && createCount == 0)
			{
				NormalEnemyCreate();
				ShieldCreate();
				attack = false;
				getTime = 0;
			}
			if (recovery != 0)
			{
				recoveryTime++;
				if (recoveryTime >= 60)
				{
					HP++;
					recoveryTime = 0;
				}
			}
			else
			{
				attack = true;
			}

		}
	}
	Attack3Move();
	Death();
}

void Enemy::Draw()
{
	boss->SetPosition(position);
	XMFLOAT3 pos{};
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() == OBJECTMEMBER::PLAYER)
		{
			pos = gameobject->GetPosition();
			radian_y = atan2f(position.x - pos.x, position.z - pos.z);
			radian_x = -atan2f(position.y - pos.y, position.z - pos.z);
			rotation.x = radian_x * (180 / M_PI);
			rotation.y = radian_y * (180 / M_PI);
			break;
		}
	}

	boss->SetRotation(rotation);
	boss->Update();
	boss->Draw();
}

void Enemy::Move()
{

	MoveLimit();

	if (!(directionX == 0) || !(directionY == 0))return;

	if (getTime == 0)
	{
		XMFLOAT3 pos{};
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::ROCK)continue;
			{
				pos = gameobject->GetPosition();
				break;
			}
		}
		getTime = 1;
		speed = 1;
		//照準との距離を計算して逃げるような動きを作る
		dx = position.x - pos.x;
		dy = position.y - pos.y;
		da = dx * dx + dy + dy;
		L = sqrt(da);
	}
	else
	{
		getTime++;
		if (getTime > 120)
		{
			getTime = 0;
		}
	}
	if (L >= 10)return;
	speed -= 0.02;
	if (moveFlag != true)return;
	if (dx < 0)
	{
		position.x -= speed;
	}
	else
	{
		position.x += speed;
	}
	if (dy < 0)
	{
		position.y -= speed;
	}
	else
	{
		position.y += speed;
	}
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
		moveFlag = false;
	}
}

void Enemy::Attack1()
{
	if (attackFlag == 0 && attackFlag3 == 0 && attackFlag4 == 0)
	{
		EnemyBullet* bullet = new EnemyBullet();
		bullet->BaseInitialize(input, audio, mouse, collision, referenceGameObjects);
		bullet->Initialize();
		addGameObjects.push_back(bullet);
		bullet->Create(position);
		attackFlag = 1;
		attackCount = 1;
	}
}

void Enemy::Attack2()
{
	if (attackFlag3 == 0)
	{
		if (coolCount == 0)
		{
			EnemyBarrage* barrage = new EnemyBarrage();
			barrage->BaseInitialize(input, audio, mouse, collision, referenceGameObjects);
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
	XMFLOAT3 pos;
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::PLAYER)continue;
		pos = gameobject->GetPosition();
		break;
	}
	if (attackFlag3 == 1)
	{
		homingTime++;
		if (homingTime >= 2)
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
		if (pos.z - 30 >= position.z)
		{
			moveFlag = false;
			position = { 0,120,100 };
			rotation = { 0,0,0 };
			ct = 250;
			rotCount = 0;
			attackFlag3 = 0;
			homingCount = 0;
			homingTime = 0;
			rushCount = 0;
			speed = 1;
			for (GameObject* gameobject : referenceGameObjects)
			{
				if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::PLAYER)continue;
				gameobject->SetRushCount(0);
				break;
			}
		}
	}
}

void Enemy::RushHit()
{
	rushCount = 1;
}

void Enemy::Hit()
{
	if (recovery != 0)return;
	HP -= 1;
}

void Enemy::Death()
{
	if (HP <= 0)
	{
		deathFlag = true;
	}
}

void Enemy::NormalEnemyCreate()
{
	for (int i = 0; i < 4; i++)
	{
		NormalEnemy* enemy = new NormalEnemy();
		enemy->BaseInitialize(input, audio, mouse, collision, referenceGameObjects);
		enemy->Initialize(position);
		addGameObjects.push_back(enemy);
		enemy->Create(i);
		recovery = 4;
	}
	createCount = 1;
}

void Enemy::ShieldCreate()
{
	Shield* shield = new Shield;
	shield->BaseInitialize(input, audio, mouse, collision, referenceGameObjects);
	shield->Initialize(position);
	addGameObjects.push_back(shield);
	shield->Create();
}

void Enemy::Attack4()
{
	if (attackFlag == 0 && attackFlag3 == 0 && attackFlag4 == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			rocket* roket = new rocket();
			roket->BaseInitialize(input, audio, mouse, collision, referenceGameObjects);
			roket->Initialize(position);
			addGameObjects.push_back(roket);
			roket->Create(i);
			attackFlag4 = 1;
		}
		attackCount = 0;
	}
}
