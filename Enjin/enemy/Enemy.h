#include"Object3d.h"
#include"Model.h"
#include"SafeDelete.h"
#include"Player.h"
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
	void Initialize(Player* player);

	void Update();

	void Draw();

	//�_���Č����Ă���U��
	void Attack1();
	void Attack1Move();

	//�e���U��
	void Attack2();
	void Attack2Move();

	//�e���U��
	void Attack3();
	void Attack3Move();

	//getter
	XMFLOAT3 GetPosition() { return enemy.rotation; }

	int GetCount() { return b.flag; }

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

		int ct = 180;//�ːi�U���̃N�[���^�C��	

		int barrageTime = 0;
		int rotCount = 0;
	};
	ENEMY enemy;

#define BULLET_MAX 50
	//�U���t���O
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,0 };
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

	XMFLOAT3 pPosition = { 0,0,0 };

	int homingTime = 0;
	int homingCount = 0;

private://�����o�ϐ�



	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;

	//�_���Č����Ă���
	Model* modelBullet = nullptr;
	Object3d* bullet = nullptr;


	//�e��
	Object3d* bulletBarrage[BULLET_MAX];

	Player* player = nullptr;

};

