#pragma once
#include"GameObject.h"
#include "EnemyBullet.h"
class NormalEnemy : public GameObject
{
public:
	NormalEnemy();
	~NormalEnemy();
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Create(int move);

	void Hit();

	void Death();

private:
	void Move();
	void MoveLimit();
	void Attack();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;

	int attackTime = 0;
};

