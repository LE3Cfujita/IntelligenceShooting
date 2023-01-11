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
	time = maxTime;
	speed = 0;
	pos = (rand() % 5 + 1) * 0.1;
}

void Efect::Move()
{
	if (count == 0)
	{
		position.x -= pos;
	}
	else if (count == 1)
	{
		position.x += pos;
	}
	time -= 1;
	if (time >= maxTime / 2)
	{
		position.y += 0.3;
		rotation.x += 30;
		rotation.z += 30;
	}
	else
	{
		speed += 0.1;
		position.y -= speed;
		rotation.x += 30;
		rotation.z += 30;
	}

	if (position.y <= -100)
	{
		deathFlag = true;
	}
}
