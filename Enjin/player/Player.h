#include"Model.h"
#include"Object3d.h"
#include"Input.h"
#include"SafeDelete.h"

#pragma once
class Player
{
private:
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Player();
	~Player();

	//‰Šú‰»
	void Initialize(Input* input);

	void Update();

	void Draw();

	void Move();

	void Attack();

	//getter
	XMFLOAT3 GetPosition() { return position; }

public:

#define BULLET_MAX 100

	//•Ï”
	XMFLOAT3 position = { 0,0,-5 };
	XMFLOAT3 rotation = { 0,-90,0 };


	//UŒ‚ƒtƒ‰ƒO
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,0 };
		XMFLOAT3 rotation = { 0,-90,0 };
	};
	BULLET b[BULLET_MAX];

	int attackCT = 0;

private://ƒƒ“ƒo•Ï”

	Input* input = nullptr;


	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

	Model* modelBullet = nullptr;
	Object3d* bullet[BULLET_MAX];

};

