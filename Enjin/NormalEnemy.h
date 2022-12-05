#pragma once
#include"GameObject.h"
class NormalEnemy : public GameObject
{
public:
	NormalEnemy();
	~NormalEnemy();
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();



private:
	Model* model = nullptr;
	Object3d* obj = nullptr;
	int maxHP = 50;
};

