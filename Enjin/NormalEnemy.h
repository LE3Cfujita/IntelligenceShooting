#pragma once
#include"GameObject.h"
class NormalEnemy : public GameObject
{

public:
	NormalEnemy();
	~NormalEnemy();

	//初期化
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Create(int move);

	void Move();
	void MoveLimit();

	//プレイヤー弾ヒット
	void Hit();

	void Death();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;

	int moveCount = 0;

};

