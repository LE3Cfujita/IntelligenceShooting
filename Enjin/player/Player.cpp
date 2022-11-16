#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(modelPlayer);
	safe_delete(player);
}

void Player::Initialize()
{
	objectMember = GameObject::PLAYER;
	HP = 300;
	//OBJ���烂�f���f�[�^��ǂݍ���
	modelPlayer = Model::LoadFormOBJ("player");
	//3D�I�u�W�F�N�g����
	player = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	player->SetModel(modelPlayer);

	player->SetPosition(position);
	player->SetRotation(rotation);
	player->SetScale({ 0.5,0.7,0.5 });

	GetKey();


}

void Player::Update()
{

}

void Player::Draw()
{
	Move();
	player->Update();
	player->Draw();
}

void Player::Move()
{
	if (input->PushKey(moveLeft) == true)
	{
		if (position.x >= -20)
		{
			position.x -= 0.3;
			rotation.x = 5;
		}
	}
	else if (input->PushKey(moveRight) == true)
	{
		if (position.x <= 20)
		{
			position.x += 0.3;
			rotation.x = -5;
		}
	}
	else
	{
		rotation.x = 0;
	}
	if (input->PushKey(moveUp) == true)
	{
		if (position.y <= 13)
		{
			position.y += 0.3;
		}
	}
	else if (input->PushKey(moveDown) == true)
	{
		if (position.y >= -7)
		{
			position.y -= 0.3;
		}
	}
	player->SetPosition(position);
	player->SetRotation(rotation);
}

void Player::Hit()
{
	HP -= 1;
}

void Player::RushHit()
{
	HP -= 10;
}


void Player::GetKey()
{
	for (GameObject* gameobject : referenceGameObjects)
	{
		
		moveLeft = gameobject->GetLeftKey();
		moveRight = gameobject->GetRightKey();
		moveUp = gameobject->GetUpKey();
		moveDown = gameobject->GetDownKey();
		attackKey = gameobject->GetAttackKey();
	}
}
