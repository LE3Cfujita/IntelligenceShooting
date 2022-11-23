#pragma once
#include"GameObject.h"
#include "EnemyBullet.h"
#include "EnemyBarrage.h"
class Enemy : public GameObject
{

private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Enemy();
	~Enemy();

	//������
	void Initialize();

	void Update();

	void Draw();

	void Move();
	void MoveLimit();

	//�_���Č����Ă���U��
	void Attack1();

	//�e���U��
	void Attack2();

	//�e���U��
	void Attack3();
	void Attack3Move();

	//�ːi�U���q�b�g
	void RushHit();

	//�v���C���[�e�q�b�g
	void Hit();

	void Death();


public:

	

private://�����o�ϐ�
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;
};

