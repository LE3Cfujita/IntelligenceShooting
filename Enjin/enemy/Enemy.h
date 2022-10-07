#include"Player.h"
#include"Aim.h"
#pragma once
class Enemy : public GameManager
{
public:
	Enemy();
	~Enemy();

	//������
	void Initialize(Player* player);

	void Update();

	void Draw();

	

	//�ʏ�e�q�b�g
	void BHit();
	void BarrageHit();

	//�ːi�U���q�b�g
	void RushHit();

	//�v���C���[�e�q�b�g
	void PHit();
private:
	void Move();

	//�_���Č����Ă���U��
	void Attack1();
	void Attack1Move();

	//�e���U��
	void Attack2();
	void Attack2Move();

	//�e���U��
	void Attack3();
	void Attack3Move();
public:

	//�U���t���O
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,100 };
		XMFLOAT3 rotation = { 0,90,0 };

		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;

		float speed = 3;
		
		XMFLOAT3 direction = { 0,0,0 };
	};
	BULLET b;//�_���Č����Ă���
	BULLET barrage[BULLET_MAX];//�e��

	int barrageNumber = 0;

	void PlusNumber();

	XMFLOAT3 pPosition = { 0,0,0 };

	int homingTime = 0;
	int homingCount = 0;

	struct AIM
	{
		XMFLOAT3 rPosition = { 0,0,0 };

		float dx = 0;
		float dy = 0;
		float da = 0;
		float L = 0;

		int directionCount = 0;
		int directionTime = 0;
	};
	AIM rock;

	XMFLOAT3 GetBPosition() { return b.position; }
	int GetBFlag() { return b.flag; }

	XMFLOAT3 GetBarragePosition() { return barrage[barrageNumber].position; }
	int GetBarrageFlag() { return barrage[barrageNumber].flag; }


private://�����o�ϐ�

	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;

	//�_���Č����Ă���
	Model* modelBullet = nullptr;
	Object3d* bullet = nullptr;


	//�e��
	Object3d* bulletBarrage[BULLET_MAX];

	Player* player = nullptr;
	Aim* aim = nullptr;

};

