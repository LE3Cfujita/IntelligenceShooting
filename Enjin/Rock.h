#pragma once
#include"Model.h"
#include"Object3d.h"
#include"SafeDelete.h"
#include"Input.h"
#include"Mouse.h"

using namespace DirectX;

class Rock
{
public:
	Rock();
	~Rock();
	void Initialize(Mouse* mouse);

	void Update();

	void Draw();

	XMFLOAT3 GetPosition() { return position; }


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
	int GetSensi() { return sensi; }
	int GetDrawSensi() { return drawSensi; }

private:
	Mouse* mouse = nullptr;
	Model* model= nullptr;
	Object3d* rock = nullptr;

	XMFLOAT3 position = { 0,0,100 };
	XMFLOAT3 rotation = { 0,90,0 };


	int sensi = 50;
	int drawSensi = 50;
};

