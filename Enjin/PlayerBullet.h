#pragma once
#include"GameObject.h"
#include <math.h>

using namespace DirectX;
class PlayerBullet : public GameObject
{
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(XMFLOAT3 pos);

	void Update();

	void Draw();

	void Move();

	void Create();



	void Hit();

#define PBULLET_MAX 50
private:
	Model* model = nullptr;
	Object3d* bullet;


};

