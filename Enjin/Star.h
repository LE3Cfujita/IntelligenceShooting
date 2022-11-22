#pragma once
#include"GameObject.h"
class Star : public GameObject
{
public:
	Star();
	~Star();

	//‰Šú‰»
	void Initialize();

	void Update();

	void Draw();

	void Move();

	void Create();

private:
	Model* model = nullptr;
	Object3d* obj = nullptr;
};

