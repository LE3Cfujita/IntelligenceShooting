#include"Model.h"
#include"Object3d.h"
#include"Input.h"
#include"SafeDelete.h"
#include"Mouse.h"
#include"OptionKey.h"

#pragma once
class Player
{
private:
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Player();
	~Player();

	//èâä˙âª
	void Initialize(Input* input, Mouse* mouse,OptionKey*key);

	void Update();

	void Draw();

	void Move();

	void Attack();

	void AttackMove();

	void PlusNumber();

	//ìGÇÃçUåÇÇ™ìñÇΩÇ¡ÇΩéû
	void Hit();
	//ìGÇÃìÀêiçUåÇÇ™ìñÇΩÇ¡ÇΩéû
	void RushHit();
	//ÉvÉåÉCÉÑÅ[ÇÃçUåÇÇ™ìGÇ…ìñÇΩÇ¡ÇΩéû
	void PHit();

	//getter
	XMFLOAT3 GetPosition() { return position; }

	int GetHP() { return HP; }

	XMFLOAT3 GetAimPosition() { return rock.position; }

	int GetBFlag() { return b[bulletNumber].flag; };
	XMFLOAT3 GetBPosition() { return b[bulletNumber].position; };

	void GetKey();

	void SetSensi(int sensi,int drawSensi) 
	{ 
		if (sensi > 100)
		{
			sensi = 10;
			drawSensi = 100;
		}
		else if (sensi == 100)
		{
			drawSensi = 1;
		}
		this->sensi = sensi;
		this->drawSensi = drawSensi;
	}
	int GetSensi() { return sensi; }
	int GetDrawSensi() { return drawSensi; }
public:

#define PBULLET_MAX 50

	//ïœêî
	XMFLOAT3 position = { 0,0,-5 };
	XMFLOAT3 rotation = { 0,-90,0 };

	int HP = 30;

	//çUåÇÉtÉâÉO
	struct BULLET
	{
		int flag = 0;

		XMFLOAT3 position = { 100,100,0 };
		XMFLOAT3 rotation = { 0,-90,0 };

		int homingTime = 0;
		int homingCount = 0;

		float dx = 0;
		float dy = 0;
		float dz = 0;
		float da = 0;
		float L = 0;
		
		float speed = 3;
	};
	BULLET b[PBULLET_MAX];

	int bulletNumber = 0;

	int attackCT = 0;

	struct AIM
	{
		XMFLOAT3 position = { 0,0,100 };
		XMFLOAT3 rotation = { 0,90,0 };

	};
	AIM rock;


private://ÉÅÉìÉoïœêî

	Input* input = nullptr;
	Mouse* mouse = nullptr;

	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

	Model* modelBullet = nullptr;
	Object3d* bullet[PBULLET_MAX];

	Model* modelAim = nullptr;
	Object3d* aim = nullptr;

	OptionKey* key = nullptr;
	int moveLeft = 0;
	int moveRight = 0;
	int moveUp = 0;
	int moveDown = 0;
	int attackKey = 0;

	int sensi = 50;
	int drawSensi = 50;
};

