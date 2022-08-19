#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(modelPlayer);
	safe_delete(player);
}

void Player::Initialize(Input* input, Mouse* mouse)
{
	this->input = input;
	this->mouse = mouse;

	//OBJ���烂�f���f�[�^��ǂݍ���
	modelPlayer = Model::LoadFormOBJ("player");
	modelBullet = Model::LoadFormOBJ("bullet");
	modelAim = Model::LoadFormOBJ("aim");
	//3D�I�u�W�F�N�g����
	player = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	player->SetModel(modelPlayer);

	player->SetPosition(position);
	player->SetRotation(rotation);
	player->SetScale({ 0.5,0.7,0.5 });


	//�e
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i] = Object3d::Create();
		bullet[i]->SetModel(modelBullet);
		bullet[i]->SetPosition(b[i].position);
		bullet[i]->SetRotation(b[i].rotation);
		bullet[i]->SetScale({ 0.7,0.7,0.7 });
	}
	//�Ə�
	aim = Object3d::Create();
	aim->SetModel(modelAim);
	rock.position.z = 30;
	aim->SetPosition(rock.position);
	aim->SetRotation(rock.rotation);
	aim->SetScale({ 1,1,1 });


}

void Player::Update()
{

	Move();
	Attack();

	player->Update();
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet[i]->Update();
	}
	aim->Update();
}

void Player::Draw()
{
	player->Draw();

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (b[i].flag == 1)
		{
			bullet[i]->Draw();
		}
	}
	aim->Draw();
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

	XMFLOAT2 mouseM{ mouse->GetMouseVelocityX() ,mouse->GetMouseVelocityY() };

	rock.position.x += mouseM.x / 12;
	rock.position.y -= mouseM.y / 12;


	player->SetPosition(position);
	player->SetRotation(rotation);
	aim->SetPosition(rock.position);
}

void Player::Attack()
{
	if (attackCT == 0)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (input->PushKey(DIK_SPACE) == true)
			{
				if (b[i].flag == 0)
				{
					b[i].flag = 1;
					b[i].position = position;
					attackCT = 1;
					break;
				}
			}
		}
	}
	else
	{
		attackCT += 1;
		if (attackCT >= 10)
		{
			attackCT = 0;
		}
	}


	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (b[i].flag == 1)
		{
			b[i].position.z += 1;
		}

		if (b[i].position.z>=100)
		{
			b[i].flag = 0;
		}
		bullet[i]->SetPosition(b[i].position);
	}

}
