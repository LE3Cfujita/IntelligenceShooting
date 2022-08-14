#include"Object3d.h"
#include"Model.h"
#include"SafeDelete.h"
#pragma once
class Enemy
{

private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Enemy();
	~Enemy();

	//������
	void Initialize();

	void Update();

	void Draw();



	//getter
	XMFLOAT3 GetPosition() { return position; }

public:
	//�ϐ�
	XMFLOAT3 position = { 0,0,50 };
	XMFLOAT3 rotation = { 0,90,0 };
	XMFLOAT3 scale = { 3,3,3 };

private://�����o�ϐ�


	Model* model = nullptr;
	Object3d* boss = nullptr;



};

