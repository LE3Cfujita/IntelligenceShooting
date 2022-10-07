#pragma once
#include"Mouse.h"
#include"GameManager.h"
class Aim : public GameManager
{
public:
	void Initialize(Mouse* mouse);
	void Update();
	void Draw();
private:


	Mouse* mouse = nullptr;
	Model* modelAim = nullptr;
	Object3d* aim = nullptr;

};

