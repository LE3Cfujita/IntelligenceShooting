#include"Player.h"
#include"Aim.h"
#pragma once
class Enemy : public GameManager
{
public:
	Enemy();
	~Enemy();

	//‰Šú‰»
	void Initialize(Player* player);

	void Update();

	void Draw();

	

	//’Êí’eƒqƒbƒg
	void BHit();
	void BarrageHit();

	//“ËiUŒ‚ƒqƒbƒg
	void RushHit();

	//ƒvƒŒƒCƒ„[’eƒqƒbƒg
	void PHit();
private:
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
public:

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
	BULLET barrage[BULLET_MAX];//’e–‹

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

	XMFLOAT3 GetBPosition() { return b.position; }
	int GetBFlag() { return b.flag; }

	XMFLOAT3 GetBarragePosition() { return barrage[barrageNumber].position; }
	int GetBarrageFlag() { return barrage[barrageNumber].flag; }


private://ƒƒ“ƒo•Ï”

	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;

	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	Model* modelBullet = nullptr;
	Object3d* bullet = nullptr;


	//’e–‹
	Object3d* bulletBarrage[BULLET_MAX];

	Player* player = nullptr;
	Aim* aim = nullptr;

};

