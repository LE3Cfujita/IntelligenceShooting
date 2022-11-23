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

	//“ËiUŒ‚ƒqƒbƒg
	void RushHit();

	//ƒvƒŒƒCƒ„[’eƒqƒbƒg
	void Hit();

	void Death();


public:

	

private://ƒƒ“ƒo•Ï”
	Model* modelBoss = nullptr;
	Object3d* boss = nullptr;
};

