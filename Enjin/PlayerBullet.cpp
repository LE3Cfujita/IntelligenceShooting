#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
	safe_delete(model);
	safe_delete(bullet);
}

void PlayerBullet::Initialize()
{
	speed = 7;
	objectMember = OBJECTMEMBER::PLAYERBULLET;
	rotation = { 0,-90,0 };
	model = Model::LoadFormOBJ("bullet");
	//�e
	bullet = Object3d::Create();
	bullet->SetModel(model);
	bullet->SetRotation(rotation);
	bullet->SetScale({ 0.7,0.7,0.7 });
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

	if (deathFlag == false)
	{
		homingTime++;
		if (homingTime >= 5)
		{
			homingTime = 0;
			homingCount = 1;
		}
		//�J�E���g��0�Ȃ�z�[�~���O����
		if (homingCount == 0)
		{
			for (GameObject* gameobject : referenceGameObjects)
			{
				if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::ROCK)
				{
					dx = position.x - gameobject->GetPosition().x;//X�̋����̌v�Z
					dy = position.y - gameobject->GetPosition().y;//Y�̋����̌v�Z
					dz = position.z - gameobject->GetPosition().z;//Z�̋����̌v�Z
					//���[�g�̒��̌v�Z
					da = dx * dx + dy * dy + dz * dz;
					//da = dx * dx + dy * dy;
					L = sqrt(da);
				}
			}
		}
		//�e�̈ړ�
		position.x -= (dx / L) * speed;
		position.y -= (dy / L) * speed;
		position.z -= (dz / L) * speed;
	}

	if (position.z >= 100)
	{
		deathFlag = true;
		homingCount = 0;
	}
	bullet->SetPosition(position);
}

void PlayerBullet::Create()
{
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::PLAYERBULLET)continue;
		if (deathFlag == true)
		{
			deathFlag = false;
			position = gameobject->GetPosition();;
			attackCT = 1;
		}
	}

}


void PlayerBullet::Hit()
{
	deathFlag = true;
	homingCount = 0;
	position.x = 1000;
}