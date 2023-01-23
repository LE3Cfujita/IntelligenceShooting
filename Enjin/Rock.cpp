#include "Rock.h"

Rock::Rock()
{
}

Rock::~Rock()
{
	safe_delete(model);
	safe_delete(rock);
}

void Rock::Initialize()
{

	objectMember = OBJECTMEMBER::ROCK;
	position = { 0.0f, 0.0f,80.0f };
	rotation = { 0,90,0 };
	model = Model::LoadFormOBJ("aim");

	//Æ€
	rock = Object3d::Create();
	rock->SetModel(model);
	rock->SetPosition(position);
	rock->SetRotation(rotation);
	rock->SetScale({ 3,3,3 });
}

void Rock::Update()
{

	XMFLOAT2 mouseM{ mouse->GetMouseVelocityX() ,mouse->GetMouseVelocityY() };

	position.x += mouseM.x / sensi;
	position.y -= mouseM.y / sensi;
	position.z = 80.0f;
	rock->SetPosition(position);
}

void Rock::Draw()
{
	rock->Update();
	rock->Draw();
}
