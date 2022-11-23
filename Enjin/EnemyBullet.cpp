#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
	safe_delete(model);
	safe_delete(bullet);
}

void EnemyBullet::Initialize()
{

	objectMember = OBJECTMEMBER::ENEMYBULLET;
	position = { 100,100,100 };
	rotation = { 0,90,0 };
	radius = 1;
	model = Model::LoadFormOBJ("enemyBullet");
	bullet = Object3d::Create();
	bullet->SetModel(model);
	bullet->SetPosition(position);
	bullet->SetRotation(rotation);
	bullet->SetScale({ 0.7,0.7,0.7 });
	speed = 2;
}

void EnemyBullet::Update()
{
	Move();
}

void EnemyBullet::Draw()
{

	bullet->Update();
	bullet->Draw();
}

void EnemyBullet::Create(XMFLOAT3 ePos)
{
	position = ePos;
	homingCount = 0;
	deathFlag = false;

	bullet->SetPosition(position);
}

void EnemyBullet::Move()
{
	XMFLOAT3 pos = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::PLAYER)continue;
		pos = gameobject->GetPosition();
		break;
	}

	homingTime++;
	if (homingTime >= 30)
	{
		homingTime = 0;
		homingCount = 1;
	}
	//�J�E���g��0�Ȃ�z�[�~���O����
	if (homingCount == 0)
	{

		dx = pos.x - position.x;//X�̋����̌v�Z
		dy = pos.y - position.y;//Y�̋����̌v�Z
		dz = pos.z - position.z;//Z�̋����̌v�Z
		//���[�g�̒��̌v�Z
		da = dx * dx + dy * dy + dz * dz;
		L = sqrt(da);
	}
	//�e�̈ړ�
	position.x += (dx / L) * speed;
	position.y += (dy / L) * speed;
	position.z += (dz / L) * speed;


	if (pos.z - 10 > position.z)
	{
		for (GameObject* gameobject : referenceGameObjects)
		{
			if (gameobject->GetObjectMember() != OBJECTMEMBER::ENEMY)continue;
			gameobject->SetAttackFlag(0);
			deathFlag = true;
			position = { 100,100,100 };
			break;
		}
	}

	bullet->SetPosition(position);
}

void EnemyBullet::Hit()
{
	deathFlag = true;
	position.z = 100;
	bullet->SetPosition(position);
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::ENEMY)continue;
		gameobject->SetAttackFlag(0);
	}

}
