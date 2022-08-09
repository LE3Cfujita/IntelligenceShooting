#include"Object3d.h"
#include"Model.h"
#include"SafeDelete.h"
#pragma once
class Enemy
{

private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Enemy();
	~Enemy();

	//初期化
	void Initialize();

	void Update();

	void Draw();



	//getter
	XMFLOAT3 GetPosition() { return position; }

public:
	//変数
	XMFLOAT3 position = { 0,0,-5 };
	XMFLOAT3 rotation = { 0,90,0 };

private://メンバ変数


	Model* model = nullptr;
	Object3d* boss = nullptr;



};

