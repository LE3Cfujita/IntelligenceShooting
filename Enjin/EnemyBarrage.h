#pragma once
#include"Model.h"
#include"Object3d.h"
#include"SafeDelete.h"

using namespace DirectX;

class EnemyBarrage
{
public:
	EnemyBarrage();
	~EnemyBarrage();
	void Initialize();

	void Update();

	void Draw();

	void Create(XMFLOAT3 ePos);

	void Hit();

	void Move(XMFLOAT3 pPos);

	void PlusNumber();

	XMFLOAT3 GetBarragePosition() { return position[number]; }
	int GetBarrageFlag() { return flag[number]; }

private:
#define EBULLET_MAX 50
	
	//‘_‚Á‚ÄŒ‚‚Á‚Ä‚­‚é
	Model* model = nullptr;
	//’e–‹
	Object3d* bullet[EBULLET_MAX];

	int flag[EBULLET_MAX];

	XMFLOAT3 position[EBULLET_MAX];
	XMFLOAT3 rotation[EBULLET_MAX];

	float dx[EBULLET_MAX];
	float dy[EBULLET_MAX];
	float dz[EBULLET_MAX];
	float da[EBULLET_MAX];
	float L[EBULLET_MAX];

	float speed = 1.5;

	int homingTime = 0;
	int homingCount = 0;
	float directionX[EBULLET_MAX];
	float directionY[EBULLET_MAX];
	XMFLOAT3 direction = { 0,0,0 };

	int coolTime = 0;
	int coolCount = 0;

	int number = 0;
};

