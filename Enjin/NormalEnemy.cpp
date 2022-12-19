#include "NormalEnemy.h"

NormalEnemy::NormalEnemy()
{
}

NormalEnemy::~NormalEnemy()
{
	safe_delete(obj);
}

void NormalEnemy::Initialize(XMFLOAT3 pos)
{
	position = pos;
	radius = 3;
	HP = 1;
	speed = 0.5;
	objectMember = OBJECTMEMBER::NORMALENEMY;
	//OBJからモデルデータを読み込む
	model = Model::CreateModel(7);
	//3Dオブジェクト生成
	obj = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	obj->SetModel(model);
	obj->SetScale({ 1.5,1.5,1.5 });
}

void NormalEnemy::Update()
{
	Move();
	Death();
}

void NormalEnemy::Draw()
{
	obj->SetPosition(position);
	obj->SetRotation(rotation);
	obj->Update();
	obj->Draw();
}

void NormalEnemy::Create(int move)
{
	deathFlag == false;
	if (move == 0)
	{
		directionX = 1;
		directionY = 1;
	}
	else if (move == 1)
	{
		directionX = 2;
		directionY = 1;
	}
	else if (move == 2)
	{
		directionX = 1;
		directionY = 2;
	}
	else
	{
		directionX = 2;
		directionY = 2;
	}
}

void NormalEnemy::Hit()
{
	HP -= 1;
}

void NormalEnemy::Death()
{
	if (HP <= 0)
	{
		deathFlag = true;
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() != OBJECTMEMBER::ENEMY)continue;
			int recovery = gameobject->GetRecovery();
			gameobject->SetRecovery(recovery - 1);
			break;
		}
	}
}

void NormalEnemy::Move()
{

	XMFLOAT3 pos{};
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::PLAYER)continue;
		pos = gameobject->GetPosition();
		break;
	}
	radian_y = atan2(position.x - pos.x, position.z - pos.z);
	radian_x = -atan2(position.y - pos.y, position.z - pos.z);
	rotation.x = radian_x * (180 / M_PI);
	rotation.y = radian_y * (180 / M_PI);

	if (directionX == 1)
	{
		position.x -= speed;
	}
	else
	{
		position.x += speed;
	}
	if (directionY == 1)
	{
		position.y -= speed;
	}
	else
	{
		position.y += speed;
	}
	MoveLimit();
}

void NormalEnemy::MoveLimit()
{
	if (position.x > 90)
	{
		directionX = 1;
	}
	if (position.x < -90)
	{
		directionX = 2;
	}
	if (position.y > 60)
	{
		directionY = 1;
	}
	if (position.y < -55)
	{
		directionY = 2;
	}
}
