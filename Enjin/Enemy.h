#pragma once
#include"rocket.h"
#include"Shield.h"
#include"GameObject.h"
#include "EnemyBullet.h"
#include "EnemyBarrage.h"
#include"NormalEnemy.h"

class Enemy : public GameObject
{

public:
	Enemy();
	~Enemy();

	//‰Šú‰»
	void Initialize();

	void Update();

	void Draw();

	void Move();
	void MoveLimit();

	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚éUŒ‚
	void Attack1();

	//’e–‹UŒ‚
	void Attack2();

	//’e–‹UŒ‚
	void Attack3();
	void Attack3Move();

	//“ËiUŒ‚ƒqƒbƒg
	void RushHit();

	//ƒvƒŒƒCƒ„[’eƒqƒbƒg
	void Hit();

	void Death();
	void NormalEnemyCreate();

	void ShieldCreate();


private:

	void Attack4();
private://ƒƒ“ƒo•Ï”
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;
	int maxHP = 50;

	int attackCount = 0;;

	int createCount = 0;

	bool attack = true;
	

};

