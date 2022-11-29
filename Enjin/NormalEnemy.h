#pragma once
#include"GameObject.h"
class NormalEnemy : public GameObject
{

public:
	NormalEnemy();
	~NormalEnemy();

	//������
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Create(int move);

	void Move();
	void MoveLimit();

	//�v���C���[�e�q�b�g
	void Hit();

	void Death();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;

	int moveCount = 0;

};

