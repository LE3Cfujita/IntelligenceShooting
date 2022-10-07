#include"GameManager.h"
#include"Aim.h"
#pragma once
class Player : public GameManager
{

public:
	Player();
	~Player();
	void Initialize(Input* input,Mouse*mouse);
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
	

	//XMFLOAT3 GetAimPosition() { return rock.position; }

	int GetBFlag() { return b[bulletNumber].flag; };
	XMFLOAT3 GetBPosition() { return b[bulletNumber].position; };

public:

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
	BULLET b[BULLET_MAX];


private://�����o�ϐ�

	Input* input = nullptr;
	Mouse* mouse = nullptr;

	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;
	Aim* aim = nullptr;

	Model* modelBullet = nullptr;
	Object3d* bullet[BULLET_MAX];

};

