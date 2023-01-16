#pragma once
#include"GameObject.h"
#include"PlayerBullet.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	//������
	void Initialize();

	void Update();

	void Draw();

	void Move();

	void Attack();
	//�G�̍U��������������
	void Hit();
	//�G�̓ːi�U��������������
	void RushHit();
	void GetKey();
	
	void Efect();

private://�����o�ϐ�


	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

	int efectFlag = false;
	int efectTime = 0;
};

