#include "Aim.h"

void Aim::Initialize(Mouse* mouse)
{
	BaseInitialize(input,audio);
	modelAim = Model::LoadFormOBJ("aim");

	//Æ€
	aim = Object3d::Create();
	aim->SetModel(modelAim);

	position.z = 80;
	aim->SetPosition(position);
	aim->SetRotation(rotation);
	aim->SetScale({ 3,3,3 });

}

void Aim::Update()
{
	XMFLOAT2 mouseM{ mouse->GetMouseVelocityX() ,mouse->GetMouseVelocityY() };

	position.x += mouseM.x / 12;
	position.y -= mouseM.y / 12;


	aim->Update();
	aim->SetPosition(position);
}

void Aim::Draw()
{
	aim->Draw();
}
