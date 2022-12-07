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
	speed = 3;
	objectMember = OBJECTMEMBER::PLAYERBULLET;
	rotation = { 90,0,0 };
	model = Model::CreateModel(2);
	//’e
	bullet = Object3d::Create();
	bullet->SetPosition(position);
	bullet->SetModel(model);
	bullet->SetScale({ 0.5,0.5,0.5 });
	//bullet->SetColor({ 0, 1, 0,0 });
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
	//ƒJƒEƒ“ƒg‚ª0‚È‚çƒz[ƒ~ƒ“ƒO‚·‚é
	if (homingCount == 0)
	{
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::ROCK)
			{
				rPos = gameobject->GetPosition();
			}
		}
		dx = position.x - rPos.x;//X‚Ì‹——£‚ÌŒvŽZ
		dy = position.y - rPos.y;//Y‚Ì‹——£‚ÌŒvŽZ
		dz = position.z - rPos.z;//Z‚Ì‹——£‚ÌŒvŽZ
		//ƒ‹[ƒg‚Ì’†‚ÌŒvŽZ
		da = dx * dx + dy * dy + dz * dz;
		//da = dx * dx + dy * dy;
		L = sqrt(da);
	}
	//’e‚ÌˆÚ“®
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