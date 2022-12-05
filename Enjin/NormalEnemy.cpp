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
	radius = 2;
	HP = maxHP;
	objectMember = OBJECTMEMBER::ENEMY;
	//OBJからモデルデータを読み込む
	model = Model::CreateModel(7);
	//3Dオブジェクト生成
	obj = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	obj->SetModel(model);
	obj->SetPosition(position);
	obj->SetRotation(rotation);
	obj->SetScale({ 1,1,1 });
}

void NormalEnemy::Update()
{
}

void NormalEnemy::Draw()
{
}
