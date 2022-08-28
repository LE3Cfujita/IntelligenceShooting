#include"Model.h"
#include"Object3d.h"
#include"Input.h"
#include"SafeDelete.h"
#include"Mouse.h"

#pragma once
class Player
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Player();
	~Player();

	//������
	void Initialize(Input* input, Mouse* mouse);

	void Update();

	void Draw();

	void Move();

	void Attack();

	void AttackMove();

	void PlusNumber();

	//�G�̍U��������������
	void Hit();
	//�G�̓ːi�U��������������
	void RushHit();
	//�v���C���[�̍U�����G�ɓ���������
	void PHit();

	//getter
	XMFLOAT3 GetPosition() { return position; }

	int GetHP() { return HP; }

	XMFLOAT3 GetAimPosition() { return rock.position; }

	int GetBFlag() { return b[bulletNumber].flag; };
	XMFLOAT3 GetBPosition() { return b[bulletNumber].position; };

public:

#define PBULLET_MAX 50

	//�ϐ�
	XMFLOAT3 position = { 0,0,-5 };
	XMFLOAT3 rotation = { 0,-90,0 };

	int HP = 50;

	//�U���t���O
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,0 };
		XMFLOAT3 rotation = { 0,-90,0 };

		int homingTime = 0;
		int homingCount = 0;

		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;
		
		float speed = 3;
	};
	BULLET b[PBULLET_MAX];

	int bulletNumber = 0;

	int attackCT = 0;

	struct AIM
	{
		XMFLOAT3 position = { 0,0,100 };
		XMFLOAT3 rotation = { 0,90,0 };

	};
	AIM rock;


private://�����o�ϐ�

	Input* input = nullptr;
	Mouse* mouse = nullptr;

	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

	Model* modelBullet = nullptr;
	Object3d* bullet[PBULLET_MAX];

	Model* modelAim = nullptr;
	Object3d* aim = nullptr;

};

