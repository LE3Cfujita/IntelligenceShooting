#pragma once
#include"GameObject.h"

using namespace DirectX;

class Rock : public GameObject
{
public:
	Rock();
	~Rock();
	void Initialize();

	void Update();

	void Draw();


	int GetDrawSensi() { return drawSensi; }
	int GetSensi() { return sensi; }
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
private:
	Model* model= nullptr;
	Object3d* rock = nullptr;
	int sensi = 1;
	int drawSensi;
};

