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
	model = Model::LoadFormOBJ("enemyBullet");
	bullet = Object3d::Create();
	bullet->SetModel(model);
	bullet->SetPosition(position);
	bullet->SetRotation(rotation);
	bullet->SetScale({ 0.7,0.7,0.7 });
}

void EnemyBullet::Update()
{
	bullet->Update();
}

void EnemyBullet::Draw()
{
	if (flag == 1)
	{
		bullet->Draw();
	}
}

void EnemyBullet::Create(XMFLOAT3 ePos)
{
	position = ePos;
	homingCount = 0;
	flag = 1;

	bullet->SetPosition(position);
}

void EnemyBullet::Move(XMFLOAT3 pPos)
{
	homingTime++;
	if (homingTime >= 40)
	{
		homingTime = 0;
		homingCount = 1;
	}
	//�J�E���g��0�Ȃ�z�[�~���O����
	if (homingCount == 0)
	{
		dx = pPos.x - position.x;//X�̋����̌v�Z
		dy = pPos.y - position.y;//Y�̋����̌v�Z
		dz = pPos.z - position.z;//Z�̋����̌v�Z
		//���[�g�̒��̌v�Z
		da = dx * dx + dy * dy + dz * dz;
		L = sqrt(da);
	}
	//�e�̈ړ�
	position.x += (dx / L) * speed;
	position.y += (dy / L) * speed;
	position.z += (dz / L) * speed;

	bullet->SetPosition(position);
}

void EnemyBullet::Hit()
{
	flag = 0;
	position.z = 100;
	bullet->SetPosition(position);
}
