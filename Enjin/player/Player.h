#include"Model.h"
#include"Object3d.h"
#include"SafeDelete.h"
#include"OptionKey.h"
#include"PlayerBullet.h"

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
	void Initialize(Input* input, OptionKey*key, PlayerBullet* bullet);

	void Update();

	void Draw();

	void Move();


	

	//�G�̍U��������������
	void Hit();
	//�G�̓ːi�U��������������
	void RushHit();
	//�v���C���[�̍U�����G�ɓ���������
	void PHit();

	//getter
	XMFLOAT3 GetPosition() { return position; }

	int GetHP() { return HP; }



	void GetKey();

public:

	//�ϐ�
	XMFLOAT3 position = { 0,0,-5 };
	XMFLOAT3 rotation = { 0,-90,0 };

	int HP = 300;




private://�����o�ϐ�

	Input* input = nullptr;
	Mouse* mouse = nullptr;

	Model* modelPlayer = nullptr;
	Object3d* player = nullptr;

	PlayerBullet* bullet = nullptr;

	OptionKey* key = nullptr;
	int moveLeft = 0;
	int moveRight = 0;
	int moveUp = 0;
	int moveDown = 0;
	int attackKey = 0;

};

