#pragma once
#include <DirectXMath.h>
#include "SafeDelete.h"
#include "Object3d.h"
#include"Input.h"
#include"Mouse.h"
#include"Audio.h"
#include"Collision.h"

#define _USE_MATH_DEFINES
#include"math.h"

using namespace DirectX;
class GameObject
{
public:
	enum OBJECTMEMBER
	{
		PLAYER,
		ENEMY,
		NORMALENEMY,
		PLAYERBULLET,
		ENEMYBULLET,
		ENEMYBARRAGE,
		ENEMYROCKET,
		NONEMEMBER,
		STAR,
		ROCK,
		OPTIONKEY,
		SHIELD,
		
	};

protected:
	Input* input = nullptr;
	Mouse* mouse = nullptr;
	Audio* audio = nullptr;
	Collision* collision = nullptr;

	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	XMFLOAT3 velocity;
	XMFLOAT4 color;
	float speed;
	int attackCT;
	int number;
	bool deathFlag;
	int homingTime;
	int homingCount;
	float dx;
	float dy;
	float dz;
	float da;
	float L;
	float directionX;
	float directionY;
	XMFLOAT3 direction;
	int coolTime;
	int coolCount;
	int moveLeft;
	int moveRight;
	int moveUp;
	int moveDown;
	int attackKey;
	int HP;
	int attackFlag;//狙って撃ってくる
	int attackFlag2;//弾幕
	int attackFlag3;//突進
	int attackFlag4;//ロケット
	int ct;//突進攻撃のクールタイム	
	int barrageTime;
	int rotCount;
	int rushCount;
	int sensi;
	int drawSensi;
	int getTime;

	int left;
	int right;
	int up;
	int down;
	int attack;
	int count;

	float radius;

	int leftDecimal;
	int rightDecimal;
	int upDecimal;
	int downDecimal;
	int attackDecimal;


	//xを軸にした角度
	double radian_x;
	double radian_y;

	int recovery;
	int recoveryTime;

	OBJECTMEMBER objectMember;
public:

	GameObject() {}
	virtual ~GameObject() {
		//std::vector<GameObject*>().swap(addGameObjects);
	}
	void BaseInitialize(Input* input, Audio* audio, Mouse* mouse, Collision* collision, std::vector<GameObject*> referenceGameObjects)
	{
		objectMember = OBJECTMEMBER::NONEMEMBER;
		this->input = input;
		this->audio = audio;
		this->mouse = mouse;
		this->collision = collision;

		deathFlag = false;
		
		radius = 1;
		attackCT = 0;
		number = 0;
		position = { 100,100,100 };

		color = { 0,0,0,0 };


		dx = 0;
		dy = 0;
		dz = 0;
		da = 0;
		L = 0;


		coolTime = 0;
		coolCount = 0;

		speed = 1.5;

		homingTime = 0;
		homingCount = 0;
		directionX = 0;
		directionY = 0;
		direction = { 0,0,0 };

		HP = 10;

		getTime = 0;

		moveLeft = 0;
		moveRight = 0;
		moveUp = 0;
		moveDown = 0;
		attackKey = 0;

		attackFlag = 0;//狙って撃ってくる
		attackFlag2 = 0;//弾幕
		attackFlag3 = 0;//突進
		attackFlag4 = 0;

		ct = 250;//突進攻撃のクールタイム	

		barrageTime = 0;
		rotCount = 0;

		speed = 1;
		rushCount = 0;

		/*sensi = 50;
		drawSensi = 50;*/

		left = 0;
		right = 0;
		up = 0;
		down = 0;
		attack = 0;

		count = 0;

		//10進数表示
		leftDecimal = 0;
		rightDecimal = 0;
		upDecimal = 0;
		downDecimal = 0;
		attackDecimal = 0;


		recovery = 0;
		recoveryTime = 0;

		
		std::vector<GameObject*>().swap(addGameObjects);
		this->referenceGameObjects = referenceGameObjects;
	}
	//初期化
	virtual void Initialize() {}

	virtual void Update() {}

	virtual void Draw() {}
	virtual void Hit() {}

	XMFLOAT3 GetVelocity() { return velocity; }
	void SetVelocity(XMFLOAT3 velocity) { this->velocity = velocity; }

	float GetRadius() { return radius; }
	float GetRadius(float radius) { this->radius = radius; }

	bool GetDeathFlag() { return deathFlag; }

	XMFLOAT3 GetPosition() { return position; };

	void SetPos(XMFLOAT3 pos) { this->position = pos; }

	void SetFlag(int deathFlag) { this->deathFlag = deathFlag; }

	int GetFlag() { return deathFlag; }

	int GetHP() { return HP; }

	int GetAttackFlag3() { return attackFlag3; }
	int GetAttackFlag() { return attackFlag; }
	int GetAttackFlag4() { return attackFlag4; }
	void SetAttackFlag(int a) { this->attackFlag = a; }
	void SetAttackFlag4(int a) { this->attackFlag4 = a; }


	int GetRushCount() { return rushCount; }
	void SetRushCount(int a) { this->rushCount = a; }
	std::vector<GameObject*> addGameObjects;

	std::vector<GameObject*> referenceGameObjects;

	OBJECTMEMBER GetObjectMember() { return objectMember; }


	int GetSensi() { return sensi; }
	int GetDrawSensi() { return drawSensi; }


	int GetLeftKey() { return left; }
	int GetRightKey() { return right; }
	int GetUpKey() { return up; }
	int GetDownKey() { return down; }
	int GetAttackKey() { return attack; }

	int GetKeyCount() { return count; }
	void SetCount(int count) { this->count = count; }
	//10進数取得
	int GetLeftDecimal() { return leftDecimal; }
	int GetRightDecimal() { return rightDecimal; }
	int GetUpDecimaly() { return upDecimal; }
	int GetDownDecimal() { return downDecimal; }
	int GetAttackDecimal() { return attackDecimal; }

	void SetLeftDecimal(int left) { leftDecimal = left; }
	void SetRightDecimal(int right) { rightDecimal = right; }
	void SetUpDecimaly(int up) { upDecimal = up; }
	void SetDownDecimal(int down) { downDecimal = down; }
	void SetAttackDecimal(int attack) { attackDecimal = attack; }

	void SetRecovery(int recovery) { this->recovery = recovery; }
	int GetRecovery() { return recovery; }

	void SetSensi(int sensi, int drawSensi)
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

};

