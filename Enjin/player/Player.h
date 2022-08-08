#include"Model.h"
#include"Object3d.h"
#include"Input.h"
#include"SafeDelete.h"

#pragma once
class Player
{
private:
	// DirectX::‚ğÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Player();
	~Player();

	//‰Šú‰»
	void Initialize(Input* input);

	void Update();

	void Draw();

	void Move();

public:
	//•Ï”
	XMFLOAT3 position = { 0,0,0 };


private://ƒƒ“ƒo•Ï”

	Input* input = nullptr;


	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

};

