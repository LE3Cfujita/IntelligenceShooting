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

	//プレイヤー弾ヒット
	void Hit();

	void Death();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;

	int moveCount = 0;

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

