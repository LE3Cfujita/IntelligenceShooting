#include "Enemy.h"

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
	safe_delete(model);
	safe_delete(boss);
}

void Enemy::Initialize()
{
	//OBJ���烂�f���f�[�^��ǂݍ���
	model = Model::LoadFormOBJ("enemy");
	//3D�I�u�W�F�N�g����
	boss = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	boss->SetModel(model);
	//3D�I�u�W�F�N�g�̈ʒu���w��
	boss->SetPosition(position );
	boss->SetRotation(rotation);
	boss->SetScale(scale);
}

void Enemy::Update()
{

	boss->Update();
}

void Enemy::Draw()
{
	boss->Draw();
}
