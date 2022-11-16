#pragma once
#include"GameObject.h"
#include "EnemyBullet.h"
#include "EnemyBarrage.h"
class Enemy : public GameObject
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

	//’Êí’eƒqƒbƒg
	void BHit();
	void BarrageHit();

	//“ËiUŒ‚ƒqƒbƒg
	void RushHit();

	//ƒvƒŒƒCƒ„[’eƒqƒbƒg
	void PHit();


public:

	struct AIM
	{
		XMFLOAT3 rPosition = { 0,0,0 };

		float dx = 0;
		float dy = 0;
		float da = 0;
		float L = 0;

		int directionCount = 0;
		int directionTime = 0;

		int getTime = 0;
	};
	AIM aim;


private://ƒƒ“ƒo•Ï”
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;
};

