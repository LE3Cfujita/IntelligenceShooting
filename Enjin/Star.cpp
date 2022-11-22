#include "Star.h"

Star::Star()
{
}

Star::~Star()
{
}

void Star::Initialize()
{
	objectMember = GameObject::STAR;
	model = Model::CreateModel(3);
	obj = Object3d::Create();
	obj->SetModel(model);
	obj->SetPosition(position);
}

void Star::Update()
{
	Move();
}

void Star::Draw()
{
	obj->Update();
	obj->Draw();
}

void Star::Move()
{
	position.z -= 2;
	if (position.z < -20)
	{
		deathFlag = true;
		position.x = 100;
	}
	obj->SetPosition(position);
}

void Star::Create()
{
	int lar = rand() % 2;
	int uad = rand() % 2;

	if (uad == 0)
	{
		position.y = (rand() % 300) * 0.1;
	}
	else
	{
		position.y = (rand() % 300) * -0.1;
	}
	if (lar == 0)
	{
		if (position.y >= 25 || position.y <= -15)
		{
			position.x = (rand() % 500) * 0.1;
		}
		position.x = (rand() % 400 + 400) * 0.1;
	}
	else
	{
		if (position.y >= 25 || position.y <= -15)
		{
			position.x = (rand() % 500) * -0.1;
		}
		position.x = (rand() % 400 + 400) * -0.1;
	}
	position.z = 200;
	color.x = rand() % 100 * 0.01;
	color.y = rand() % 100 * 0.01;
	color.z = rand() % 100 * 0.01;
	rotation.x = rand() % 3610 * 0.1;
	rotation.z = rand() % 3610 * 0.1;
	scale.x = (rand() % 20 + 20) * 0.1;
	scale.y = (rand() % 20 + 20) * 0.1;
	scale.z = (rand() % 20 + 20) * 0.1;
	obj->SetColor(color);
	obj->SetPosition(position);
	obj->SetScale(scale);
	obj->SetRotation(rotation);
}
