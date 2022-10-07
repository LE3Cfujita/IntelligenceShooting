#pragma once

#include <DirectXMath.h>
#include "SafeDelete.h"
#include "Input.h"
#include "Audio.h"
#include "Object3d.h"

using namespace DirectX;

#define BULLET_MAX 100
class GameManager
{
public:
	enum OBJECTMEMBER
	{
		PLAYER,
		ENEMY,
		AIM,
	};

protected:
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	int HP;

	int bulletNumber;

	int attackCT;


	int attackFlag;//狙って撃ってくる
	int attackFlag2;//弾幕
	int attackFlag3;//突進

	int ct;//突進攻撃のクールタイム	

	int barrageTime;
	int rotCount;

	float speed;

	int directionX;
	int directionY;


	float dx;
	float dy;
	float dz;
	float da;
	float L;

	int homingTime;
	int homingCount;


	int rushCount;

	Input* input = nullptr;
	Audio* audio = nullptr;
	OBJECTMEMBER objectMember;
public:
	GameManager(){}
	~GameManager()
	{

	}

	void BaseInitialize(Input* input, Audio* audio)
	{
		position = { 0,0,0 };
		rotation = { 0,0,0 };
		scale = { 0,0,0 };
		HP = 50;
		bulletNumber = 0;
		attackCT = 0;
		attackFlag = 0;//狙って撃ってくる
		attackFlag2 = 0;//弾幕
		attackFlag3 = 0;//突進
		ct = 300;//突進攻撃のクールタイム	
		barrageTime = 0;
		rotCount = 0;
		speed = 1;
		directionX = 0;
		directionY = 0;
		dx = 0;
		dy = 0;
		dz = 0;
		da = 0;
		L = 0;
		homingTime = 0;
		homingCount = 0;
		rushCount = 0;

	}

	virtual void Initialize() {}
	virtual void Update() {}
	virtual void Draw() {}

	XMFLOAT3 GetPosition() { return position; }

	int GetHP() { return HP; }

	int GetCount() { return attackFlag3; }


	int GetRushCount() { return rushCount; }

	OBJECTMEMBER GetObjectMember() { return objectMember; }
};