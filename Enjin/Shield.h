#pragma once
#include"GameObject.h"
class Shield : public GameObject
{
public:
	Shield();
	~Shield();

	//èâä˙âª
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Create();

	void Motion();
private:
	Model* model = nullptr;
	Object3d* obj = nullptr;
};