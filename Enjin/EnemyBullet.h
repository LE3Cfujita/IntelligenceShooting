#pragma once
#include"Model.h"
#include"Object3d.h"
#include"SafeDelete.h"
using namespace DirectX;
class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize();

	void Update();

	void Draw();

	void Create(XMFLOAT3 ePos);

	void Move(XMFLOAT3 pPos);

	void Hit();

	void SetPos(XMFLOAT3 pos) { this->position = pos; }
	void SetFlag(int flag) { this->flag = flag; }

	int GetFlag() { return flag; }

	XMFLOAT3 GetPos() { return position; }

private:
	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	Model* model = nullptr;
	Object3d* bullet = nullptr;

	int flag = 0;

	XMFLOAT3 position = { 100,100,100 };
	XMFLOAT3 rotation = { 0,90,0 };

	float dx = 0;
	float dy = 0;
	float dz = 0;
	float da = 0;
	float L = 0;

	float speed = 1.5;

	int homingTime = 0;
	int homingCount = 0;
	float directionX = 0;
	float directionY = 0;
	XMFLOAT3 direction = { 0,0,0 };

};

