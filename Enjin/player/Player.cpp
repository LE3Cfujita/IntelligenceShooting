#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	safe_delete(modelPlayer);
}

void Player::Initialize(Input* input)
{
	this->input = input;

	//OBJからモデルデータを読み込む
	modelPlayer = Model::LoadFormOBJ("player");
	//3Dオブジェクト生成
	player = Object3d::Create();
	//オブジェクトにモデルを紐付ける
	player->SetModel(modelPlayer);

	player->SetPosition(position);
	player->SetRotation({ 0,-90,0 });
	player->SetScale({ 1,1,0.7 });
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
		position.x -= 0.3;
	}
	if (input->PushKey(DIK_D) == true)
	{
		position.x += 0.3;
	}

	if (input->PushKey(DIK_W) == true)
	{
		position.y += 0.3;
	}
	if (input->PushKey(DIK_S) == true)
	{
		position.y -= 0.3;
	}

	player->SetPosition(position);
}
