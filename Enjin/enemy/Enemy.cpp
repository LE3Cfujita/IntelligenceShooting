#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
	safe_delete(model);
	safe_delete(boss);
}

void Enemy::Initialize()
{
	//OBJからモデルデータを読み込む
	model = Model::LoadFormOBJ("enemy");
	//3Dオブジェクト生成
	boss = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	boss->SetModel(model);
	//3Dオブジェクトの位置を指定
	boss->SetPosition(position );
	boss->SetRotation(rotation);
	boss->SetScale(scale);
}

void Enemy::Update()
{

	boss->Update();
}

void Enemy::Draw()
{
	boss->Draw();
}
