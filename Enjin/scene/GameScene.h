#include "Input.h"
#include"Mouse.h"
#include "ObjectFBX.h"
#include "Object3d.h"
#include"Sprite.h"
#include "DebugText.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"FbxLoader.h"
#include"DebugCamera.h"
#include "SafeDelete.h"
#include <DirectXMath.h>
#include"Player.h"
#include"Enemy.h"
#include"Collision.h"


#pragma once
class GameScene
{
private://�G�C���A�X
//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio, Mouse* mouse);

	void Update(WinApp* winApp);

	void Draw();
	void Text();

	void BCollision();

	void SceneChange();

	//�}�E�X���W�擾
	POINT mouse_pos;

	XMFLOAT2 lockSize = { 64,64 };

	//���O�𖳂���
	XMFLOAT2 spritePos = { 0,0 };

	XMFLOAT2 cursor_pos = { 0,0 };

	XMFLOAT3 barragePosition[EBULLET_MAX];

	XMFLOAT3 pBPosition[PBULLET_MAX];

	int count = 0;

	int pHP = 0;

	int eHP = 0;

	//�V�[��
	int scene = 2;
private:


	//�|�C���^�u����
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Sprite* sprite = nullptr;
	DebugCamera* camera = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Mouse* mouse = nullptr;
	Collision* collision = nullptr;

	//FBX�錾
	ModelFBX* model = nullptr;

	ObjectFBX* object = nullptr;


	Object3d* object3d_3 = nullptr;


	//�f�o�b�N�e�L�X�g�p
	char str[100];
	char str2[100];
	char str3[100];
	char str4[100];

	//�X�v���C�g
	const int SPRITE_NUM = 10;
	//Sprite sprite[SPRITE_NUM];

	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 0;
};

