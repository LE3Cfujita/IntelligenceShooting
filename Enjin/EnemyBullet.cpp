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
	//カウントが0ならホーミングする
	if (homingCount == 0)
	{
		dx = pPos.x - position.x;//Xの距離の計算
		dy = pPos.y - position.y;//Yの距離の計算
		dz = pPos.z - position.z;//Zの距離の計算
		//ルートの中の計算
		da = dx * dx + dy * dy + dz * dz;
		L = sqrt(da);
	}
	//弾の移動
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
