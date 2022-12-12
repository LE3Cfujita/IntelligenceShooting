#include "rocket.h"

rocket::rocket()
{
}

rocket::~rocket()
{
	safe_delete(obj);
}

void rocket::Initialize(XMFLOAT3 pos)
{
	objectMember = OBJECTMEMBER::ENEMYROCKET;
	position = pos;
	radius = 2;
	model = Model::CreateModel(6);
	obj = Object3d::Create();
	obj->SetModel(model);
	obj->SetPosition(position);
	obj->SetRotation(rotation);
	obj->SetScale({ 1,1,0.7 });
	speed = 1;
}

void rocket::Update()
{
	Move();
}

void rocket::Draw()
{
	obj->SetRotation(rotation);
	obj->SetPosition(position);
	obj->Update();
	obj->Draw();
}

void rocket::Create(int move)
{
	deathFlag == false;
	moveCount = move;

}

void rocket::Move()
{

	XMFLOAT3 pos{};
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::PLAYER)continue;
		pos = gameobject->GetPosition();
		break;
	}
	if (speed >= 0)
	{
		if (moveCount == 0)
		{
			position.x += speed;
		}
		else
		{
			position.x -= speed;
		}
		speed -= 0.02;
		radian_y = atan2(position.x - pos.x, position.z - pos.z);
		radian_x = -atan2(position.y - pos.y, position.z - pos.z);
		rotation.x = radian_x * (180 / M_PI);
		rotation.y = radian_y * (180 / M_PI);
	}
	else
	{
		homingTime++;
		if (homingTime >= 10)
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
		rotation.z += 20;
		position.x -= (dx / L) * 2;
		position.y -= (dy / L) * 2;
		position.z -= (dz / L) * 2;
		if (pos.z - 30 >= position.z)
		{
			deathFlag = true;
		}
	}
	if (pos.z - 20 > position.z)
	{
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() != OBJECTMEMBER::ENEMY)continue;
			gameobject->SetAttackFlag4(0);
			deathFlag = true;
			position = { 100,100,100 };
			break;
		}
	}

}

void rocket::Hit()
{

	deathFlag = true;
	position.z = 100;
	obj->SetPosition(position);
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::ENEMY)continue;
		gameobject->SetAttackFlag4(0);
	}
}
