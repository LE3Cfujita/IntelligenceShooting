#pragma once
#include"GameObject.h"
#include "EnemyBullet.h"
#include "EnemyBarrage.h"
#include"rocket.h"

class Enemy : public GameObject
{

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

private:

	void Attack4();
private://�����o�ϐ�
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;
	int maxHP = 500;

	int createTime;


};

