#include "NormalEnemy.h"

NormalEnemy::NormalEnemy()
{
}

NormalEnemy::~NormalEnemy()
{
	safe_delete(obj);
}

void NormalEnemy::Initialize(XMFLOAT3 pos)
{
	position = pos;
	radius = 2;
	HP = maxHP;
	objectMember = OBJECTMEMBER::ENEMY;
	//OBJ���烂�f���f�[�^��ǂݍ���
	model = Model::CreateModel(7);
	//3D�I�u�W�F�N�g����
	obj = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f����R�t����
	obj->SetModel(model);
	obj->SetPosition(position);
	obj->SetRotation(rotation);
	obj->SetScale({ 1,1,1 });
}

void NormalEnemy::Update()
{
}

void NormalEnemy::Draw()
{
}
