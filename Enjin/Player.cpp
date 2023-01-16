#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(player);
}

void Player::Initialize()
{
	objectMember = GameObject::PLAYER;
	HP = 250;
	radius = 2;
	position = { 0,0,0 };
	rotation = { 0,-90,0 };
	//OBJからモデルデータを読み込む
	modelPlayer = Model::CreateModel(4);
	//3Dオブジェクト生成
	player = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	player->SetModel(modelPlayer);

	player->SetPosition(position);
	player->SetRotation(rotation);
	player->SetScale({ 0.5,0.7,0.5 });

	GetKey();


}

void Player::Update()
{
	Move();
	Attack();
	Efect();
}

void Player::Draw()
{

	player->SetPosition(position);
	player->SetRotation(rotation);
	player->Update();
	if (efectFlag != false)return;
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
}


void Player::Attack()
{
	if (coolCount == 0)
	{
		if (input->PushKey(attackKey) || mouse->PushMouseLeft()) {
			PlayerBullet* bullet = new PlayerBullet();
			bullet->BaseInitialize(input, audio, mouse, collision, referenceGameObjects);
			bullet->Initialize(position);
			bullet->Create();
			addGameObjects.push_back(bullet);
			coolCount = 1;
		}
	}
	else
	{
		coolTime++;
		if (coolTime < 5)return;
		coolTime = 0;
		coolCount = 0;
	}
}

void Player::Hit()
{
	if (efectFlag != false)return;
	HP -= 15;
	if (efectTime < 0)
	{
		efectTime = 30;
	}
	efectFlag = true;
}

void Player::RushHit()
{
	if (efectFlag != false)return;
	if (efectTime < 0)
	{
		efectTime = 30;
	}
	efectFlag = true;
	rushCount = 1;
	HP -= 50;
}


void Player::GetKey()
{
	for (GameObject* gameobject : referenceGameObjects)
	{
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::OPTIONKEY)continue;
		moveLeft = gameobject->GetLeftKey();
		moveRight = gameobject->GetRightKey();
		moveUp = gameobject->GetUpKey();
		moveDown = gameobject->GetDownKey();
		attackKey = gameobject->GetAttackKey();
	}
}

void Player::Efect()
{
	efectTime--;
	if (efectTime > 20 || efectTime < 30 && efectTime > 20 || efectTime < 20 && efectTime > 10 || efectTime < 10 && efectTime > 0)
	{
		efectFlag = true;
	}
	else
	{
		efectFlag = false;
	}
}
