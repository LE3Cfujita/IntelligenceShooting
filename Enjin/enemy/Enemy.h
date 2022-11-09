#include"Object3d.h"
#include"Model.h"
#include"SafeDelete.h"
#include"Player.h"
#include"rock.h"
#include"EnemyBullet.h"
#include"EnemyBarrage.h"
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
	void Initialize(Player* player,Rock*rock, EnemyBullet*bullet,EnemyBarrage* barrage);

	void Update();

	void Draw();

	void Move();
	void MoveLimit();

	//�_���Č����Ă���U��
	void Attack1();
	void Attack1Move();

	//�e���U��
	void Attack2();

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



	int GetCount() { return enemy.attackFlag3; }

	int GetHP() { return enemy.HP; }

	int GetRushCount() { return enemy.rushCount; }

private://�����o�ϐ�


	EnemyBullet* bullet = nullptr;
	Rock* rock = nullptr;
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;
	EnemyBarrage* barrage = nullptr;

	Player* player = nullptr;

};

