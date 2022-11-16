#pragma once
#include"GameObject.h"

using namespace DirectX;
class PlayerBullet : public GameObject
{
public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize();

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

