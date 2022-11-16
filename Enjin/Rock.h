#pragma once
#include"GameObject.h"

using namespace DirectX;

class Rock : public GameObject
{
public:
	Rock();
	~Rock();
	void Initialize();

	void Update();

	void Draw();



private:
	Model* model= nullptr;
	Object3d* rock = nullptr;

};

