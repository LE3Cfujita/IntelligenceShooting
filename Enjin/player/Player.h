#pragma once
#include"GameObject.h"

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
	//�G�̍U��������������
	void Hit();
	//�G�̓ːi�U��������������
	void RushHit();
	void GetKey();

private://�����o�ϐ�

	Mouse* mouse = nullptr;

	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;
};

