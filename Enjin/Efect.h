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

	float pos = 0;
};

