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
	//OBJからモデルデータを読み込む
	modelBoss = Model::LoadFormOBJ("enemy");
	//3Dオブジェクト生成
	boss = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	boss->SetModel(modelBoss);

	boss->SetPosition(position);
	boss->SetRotation(rotation);
	boss->SetScale({ 4,4,4 });
}

void Enemy::Update()
{

	boss->Update();
}

void Enemy::Draw()
{
	boss->Draw();
}
