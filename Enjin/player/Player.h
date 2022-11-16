#pragma once
#include"GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	//‰Šú‰»
	void Initialize();

	void Update();

	void Draw();

	void Move();
	//“G‚ÌUŒ‚‚ª“–‚½‚Á‚½
	void Hit();
	//“G‚Ì“ËiUŒ‚‚ª“–‚½‚Á‚½
	void RushHit();
	void GetKey();

private://ƒƒ“ƒo•Ï”

	Mouse* mouse = nullptr;

	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;
};

