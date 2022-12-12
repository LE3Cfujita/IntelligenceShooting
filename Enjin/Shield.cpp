#include "Shield.h"

Shield::Shield()
{
}

Shield::~Shield()
{
	safe_delete(obj);
}

void Shield::Initialize(XMFLOAT3 pos)
{
	position = pos;
	objectMember = OBJECTMEMBER::SHIELD;
	//OBJからモデルデータを読み込む
	model = Model::CreateModel(8);
	//3Dオブジェクト生成
	obj = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	obj->SetModel(model);
	obj->SetScale({ 0,0,0 });
}

void Shield::Update()
{
	XMFLOAT3 pos = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::ENEMY)continue;
		pos = gameobject->GetPosition();
		break;
	}
	position = pos;
}

void Shield::Draw()
{
	obj->SetRotation(rotation);
	obj->SetPosition(position);
	obj->Update();
	obj->Draw();
}

void Shield::Create()
{
	deathFlag = false;
}
