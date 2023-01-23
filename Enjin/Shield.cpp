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
	position = { pos.x ,pos.y,pos.z };
	objectMember = OBJECTMEMBER::SHIELD;
	//OBJからモデルデータを読み込む
	model = Model::CreateModel(8);
	//3Dオブジェクト生成
	obj = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	obj->SetModel(model);
	obj->SetScale({ 0.1,0.1,0.1 });
}

void Shield::Update()
{
	XMFLOAT3 pos = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != OBJECTMEMBER::ENEMY)continue;
		pos = gameobject->GetPosition();
		recovery = gameobject->GetRecovery();
		break;
	}

	Motion();
	position = { pos.x,pos.y,pos.z - 30 };
}

void Shield::Draw()
{
	obj->SetScale(scale);
	obj->SetRotation(rotation);
	obj->SetPosition(position);
	obj->Update();
	obj->Draw();
}

void Shield::Create()
{
	deathFlag = false;
}

void Shield::Motion()
{
	if (scale.x < 15 && scale.y < 15 && scale.z < 15 && recovery != 0)
	{
		scale.x += 0.1;
		scale.y += 0.1;
		scale.z += 0.1;
	}

	if (recovery == 0)
	{
		scale.x -= 0.1;
		scale.y -= 0.1;
		scale.z -= 0.1;
	}
	if (scale.x < 0 && scale.y < 0 && scale.z < 0)
	{
		deathFlag = true;
	}
}
