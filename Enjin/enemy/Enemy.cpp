#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
	safe_delete(modelBoss);
	safe_delete(boss);
}

void Enemy::Initialize()
{
	//OBJ���烂�f���f�[�^��ǂݍ���
	modelBoss = Model::LoadFormOBJ("enemy");
	//3D�I�u�W�F�N�g����
	boss = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	boss->SetModel(modelBoss);

	boss->SetPosition(position);
	boss->SetRotation(rotation);
	boss->SetScale({ 4,4,4 });
}

void Enemy::Update()
{

	boss->Update();
}

void Enemy::Draw()
{
	boss->Draw();
}
