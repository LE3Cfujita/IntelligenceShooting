#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(modelPlayer);
	safe_delete(player);
}

void Player::Initialize(Input* input)
{
	this->input = input;

	//OBJ���烂�f���f�[�^��ǂݍ���
	modelPlayer = Model::LoadFormOBJ("player");
	//3D�I�u�W�F�N�g����
	player = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	player->SetModel(modelPlayer);

	player->SetPosition(position);
	player->SetRotation(rotation);
	player->SetScale({ 0.5,0.7,0.5 });
}

void Player::Update()
{

	Move();

	player->Update();
}

void Player::Draw()
{
	player->Draw();
}

void Player::Move()
{
	if (input->PushKey(DIK_A) == true)
	{
		if (position.x >= -20)
		{
			position.x -= 0.3;
			rotation.x = 5;
		}
	}
	else if (input->PushKey(DIK_D) == true)
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
	if (input->PushKey(DIK_W) == true)
	{
		if (position.y <= 13)
		{
			position.y += 0.3;
		}
	}
	else if (input->PushKey(DIK_S) == true)
	{
		if (position.y >= -7)
		{
			position.y -= 0.3;
		}
	}

	player->SetPosition(position);
	player->SetRotation(rotation);
}
