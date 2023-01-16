#include "Efect.h"

Efect::Efect()
{
	safe_delete(efect);
}

Efect::~Efect()
{
}

void Efect::Initialize(XMFLOAT3 pos)
{
	objectMember = OBJECTMEMBER::EFECT;
	model = Model::CreateModel(9);

	position = pos;
	//Æ€
	efect = Object3d::Create();
	efect->SetModel(model);
	efect->SetPosition(position);
	efect->SetScale({ 0.3,0.3,0.3 });
	efect->SetColor({ 1,0.3,0,0 });
}

void Efect::Update()
{
	Move();
}

void Efect::Draw()
{
	efect->SetPosition(position);
	efect->SetRotation(rotation);
	efect->Update();
	efect->Draw();
}

void Efect::Create(int count)
{
	deathFlag = false;
	this->count = count;
	pos = (rand() % 51) * 0.01;
}

void Efect::Move()
{
	if (count == 0)
	{
		position.x -= pos;
		position.y += 0.3;
		rotation.x += 30;
		rotation.z += 30;
	}
	else
	{
		position.x += pos;
		position.y += 0.3;
		rotation.x += 30;
		rotation.z += 30;
	}
	if (position.y <= -100)
	{
		deathFlag = true;
	}
}
