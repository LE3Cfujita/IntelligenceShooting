#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
	safe_delete(bullet);
}

void PlayerBullet::Initialize(XMFLOAT3 pos)
{
	position = pos;
	speed = 5;
	objectMember = OBJECTMEMBER::PLAYERBULLET;

	model = Model::CreateModel(2);
	//弾
	bullet = Object3d::Create();
	bullet->SetPosition(position);
	bullet->SetModel(model);
	bullet->SetScale({ 0.7,0.7,1.5 });
	XMFLOAT3 rPos{};
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() == OBJECTMEMBER::ROCK)
		{
			rPos = gameobject->GetPosition();
			radian_y = atan2f(position.x - rPos.x, position.z - rPos.z);
			radian_x = atan2f(position.y - rPos.y, position.z - rPos.z);
			rotation.x = radian_x * (180 / M_PI);
			rotation.y = radian_y * (180 / M_PI);
			break;
		}
	}
	bullet->SetRotation(rotation);
}

void PlayerBullet::Update()
{
	Move();
}

void PlayerBullet::Draw()
{
	bullet->Update();
	bullet->Draw();
}

void PlayerBullet::Move()
{
	XMFLOAT3 rPos = { 0.0f,0.0f,0.0f };
	homingTime++;
	if (homingTime >= 5)
	{
		homingTime = 0;
		homingCount = 1;
	}
	//カウントが0ならホーミングする
	if (homingCount == 0)
	{
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::ROCK)
			{
				rPos = gameobject->GetPosition();
			}
		}
		dx = position.x - rPos.x;//Xの距離の計算
		dy = position.y - rPos.y;//Yの距離の計算
		dz = position.z - rPos.z;//Zの距離の計算
		//ルートの中の計算
		da = dx * dx + dy * dy + dz * dz;
		//da = dx * dx + dy * dy;
		L = sqrt(da);
	}
	//弾の移動
	position.x -= (dx / L) * speed;
	position.y -= (dy / L) * speed;
	position.z -= (dz / L) * speed;

	if (position.z >= 100)
	{
		deathFlag = true;
		homingCount = 0;
	}
	bullet->SetPosition(position);
}

void PlayerBullet::Create()
{
	deathFlag = false;
}


void PlayerBullet::Hit()
{
	deathFlag = true;
	homingCount = 0;
	position.x = 1000;
}