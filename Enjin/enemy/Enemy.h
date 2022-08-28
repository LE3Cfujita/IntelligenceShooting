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

	void Move();

	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚éUŒ‚
	void Attack1();
	void Attack1Move();

	//’e–‹UŒ‚
	void Attack2();
	void Attack2Move();

	//’e–‹UŒ‚
	void Attack3();
	void Attack3Move();

	//’Êí’eƒqƒbƒg
	void BHit();
	void BarrageHit();

	//“ËiUŒ‚ƒqƒbƒg
	void RushHit();

	//ƒvƒŒƒCƒ„[’eƒqƒbƒg
	void PHit();


public:
	struct ENEMY
	{
		//•Ï”
		XMFLOAT3 position = { 0,0,100 };
		XMFLOAT3 rotation = { 0,180,0 };
		XMFLOAT3 scale = { 3,3,3 };

		int attackFlag = 0;//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
		int attackFlag2 = 0;//’e–‹
		int attackFlag3 = 0;//“Ëi

		int ct = 300;//“ËiUŒ‚‚ÌƒN[ƒ‹ƒ^ƒCƒ€	

		int barrageTime = 0;
		int rotCount = 0;

		float speed = 1;

		int directionX = 0;
		int directionY = 0;


		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;

		int homingTime = 0;
		int homingCount = 0;

		int HP = 100;

		int rushCount = 0;

	};
	ENEMY enemy;

#define EBULLET_MAX 100
	//UŒ‚ƒtƒ‰ƒO
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,100 };
		XMFLOAT3 rotation = { 0,90,0 };

		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;

		float speed = 3;
		
		XMFLOAT3 direction = { 0,0,0 };
	};
	BULLET b;//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	BULLET barrage[EBULLET_MAX];//’e–‹

	int barrageNumber = 0;

	void PlusNumber();

	XMFLOAT3 pPosition = { 0,0,0 };

	int homingTime = 0;
	int homingCount = 0;

	struct AIM
	{
		XMFLOAT3 rPosition = { 0,0,0 };

		float dx = 0;
		float dy = 0;
		float da = 0;
		float L = 0;

		int directionCount = 0;
		int directionTime = 0;
	};
	AIM rock;


	//getter
	XMFLOAT3 GetPosition() { return enemy.position; }

	XMFLOAT3 GetBPosition() { return b.position; }
	int GetBFlag() { return b.flag; }

	XMFLOAT3 GetBarragePosition() { return barrage[barrageNumber].position; }
	int GetBarrageFlag() { return barrage[barrageNumber].flag; }

	int GetCount() { return enemy.attackFlag3; }

	int GetHP() { return enemy.HP; }

	int GetRushCount() { return enemy.rushCount; }

private://ƒƒ“ƒo•Ï”



	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;

	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	Model* modelBullet = nullptr;
	Object3d* bullet = nullptr;


	//’e–‹
	Object3d* bulletBarrage[EBULLET_MAX];

	Player* player = nullptr;

};

