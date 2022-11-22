#pragma once
#include"GameObject.h"
#include"PlayerBullet.h"

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

	void Attack();
	//“G‚ÌUŒ‚‚ª“–‚½‚Á‚½
	void Hit();
	//“G‚Ì“ËiUŒ‚‚ª“–‚½‚Á‚½
	void RushHit();
	void GetKey();

private://ƒƒ“ƒo•Ï”


	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;
};

