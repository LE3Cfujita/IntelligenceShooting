#pragma once
#include"GameObject.h"
class Efect : public GameObject
{
public:
	Efect();
	~Efect();
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Create(int count);

	void Move();
private:
	Model* model = nullptr;
	Object3d* efect = nullptr;
	int maxTime=60;
	int time = 60;

	float pos = 0;
};

