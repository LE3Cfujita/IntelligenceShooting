#include"Object3d.h"
#include"Model.h"
#include"SafeDelete.h"
#include"Player.h"
#pragma once
class Enemy
{

private:
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Enemy();
	~Enemy();

	//‰Šú‰»
	void Initialize(Player* player);

	void Update();

	void Draw();

	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚éUŒ‚
	void Attack1();
	void Attack1Move();


	//getter
	XMFLOAT3 GetPosition() { return enemy.position; }

	int GetCount() { return b.flag; }

public:
	struct ENEMY
	{
		//•Ï”
		XMFLOAT3 position = { 0,0,100 };
		XMFLOAT3 rotation = { 0,180,0 };
		XMFLOAT3 scale = { 3,3,3 };

		int attackFlag = 0;

		
	};
	ENEMY enemy;

	//UŒ‚ƒtƒ‰ƒO
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,0 };
		XMFLOAT3 rotation = { 0,90,0 };

		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;

		float speed = 3;
	};
	BULLET b;

	XMFLOAT3 pPosition = { 0,0,0 };

	int homingTime = 0;
	int homingCount = 0;

private://ƒƒ“ƒo•Ï”



	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;

	Model* modelBullet = nullptr;
	Object3d* bullet = nullptr;

	Player* player = nullptr;

};

