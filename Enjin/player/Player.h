#include"Model.h"
#include"Object3d.h"
#include"Input.h"
#include"SafeDelete.h"

#pragma once
class Player
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Player();
	~Player();

	//������
	void Initialize(Input* input);

	void Update();

	void Draw();

	void Move();



	//getter
	XMFLOAT3 GetPosition() { return position; }

public:
	//�ϐ�
	XMFLOAT3 position = { 0,0,-5 };
	XMFLOAT3 rotation = { 0,-90,0 };

private://�����o�ϐ�

	Input* input = nullptr;


	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

};
