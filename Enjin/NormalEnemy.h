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



	void Hit();

	void Death();

private:
	void Move();
	void MoveLimit();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;
	void Move();
	void MoveLimit();

	//�v���C���[�e�q�b�g
	void Hit();

	void Death();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;

	int moveCount = 0;

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

