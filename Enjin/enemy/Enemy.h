#include"Object3d.h"
#include"Model.h"
#include"SafeDelete.h"
#include"Player.h"
#include"rock.h"
#pragma once
class Enemy
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
	void Initialize(Player* player,Rock*rock);

	void Update();

	void Draw();

	void Move();
	void MoveLimit();

	//�_���Č����Ă���U��
	void Attack1();
	void Attack1Move();

	//�e���U��
	void Attack2();
	void Attack2Move();

	//�e���U��
	void Attack3();
	void Attack3Move();

	//�ʏ�e�q�b�g
	void BHit();
	void BarrageHit();

	//�ːi�U���q�b�g
	void RushHit();

	//�v���C���[�e�q�b�g
	void PHit();


public:
	struct ENEMY
	{
		//�ϐ�
		XMFLOAT3 position = { 0,0,100 };
		XMFLOAT3 rotation = { 0,180,0 };
		XMFLOAT3 scale = { 3,3,3 };

		int attackFlag = 0;//�_���Č����Ă���
		int attackFlag2 = 0;//�e��
		int attackFlag3 = 0;//�ːi

		int ct = 300;//�ːi�U���̃N�[���^�C��	

		int barrageTime = 0;
		int rotCount = 0;

		float speed = 1;

		int directionX = 0;
		int directionY = 0;


		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;

		int homingTime = 0;
		int homingCount = 0;

		int HP = 50;

		int rushCount = 0;

	};
	ENEMY enemy;

#define EBULLET_MAX 50
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

		float speed = 1.5;

		int homingTime = 0;
		int homingCount = 0;
		float directionX = 0;
		float directionY = 0;
		XMFLOAT3 direction = { 0,0,0 };
	};
	BULLET b;//�_���Č����Ă���
	BULLET barrage[EBULLET_MAX];//�e��

	int barrageNumber = 0;

	void PlusNumber();

	XMFLOAT3 pPosition = { 0,0,0 };

	int coolTime = 0;
	int coolCount = 0;


	struct AIM
	{
		XMFLOAT3 rPosition = { 0,0,0 };

		float dx = 0;
		float dy = 0;
		float da = 0;
		float L = 0;

		int directionCount = 0;
		int directionTime = 0;

		int getTime = 0;
	};
	AIM aim;


	//getter
	XMFLOAT3 GetPosition() { return enemy.position; }

	XMFLOAT3 GetBPosition() { return b.position; }
	int GetBFlag() { return b.flag; }

	XMFLOAT3 GetBarragePosition() { return barrage[barrageNumber].position; }
	int GetBarrageFlag() { return barrage[barrageNumber].flag; }

	int GetCount() { return enemy.attackFlag3; }

	int GetHP() { return enemy.HP; }

	int GetRushCount() { return enemy.rushCount; }

private://�����o�ϐ�



	Rock* rock = nullptr;
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;

	//�_���Č����Ă���
	Model* modelBullet = nullptr;
	Object3d* bullet = nullptr;


	//�e��
	Object3d* bulletBarrage[EBULLET_MAX];

	Player* player = nullptr;

};

