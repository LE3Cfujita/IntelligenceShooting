#include "Input.h"
#include"Mouse.h"
#include "Object3d.h"
#include"Sprite.h"
#include "DebugText.h"
#include"Audio.h"
#include"DirectXCommon.h"
#include"DebugCamera.h"
#include "SafeDelete.h"
#include <DirectXMath.h>
#include"Player.h"
#include"Enemy.h"
#include"Collision.h"
#include"OptionKey.h"


#pragma once
class GameScene
{
public:
	enum GameState
	{
		TITLE,
		OPSTION_SOUND,
		OPSTION_KEY,
		PLAY,
		CLEA,
		OVER
	};
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

	void Title();

	void Option_BGMSE();
	void Option_KEY();

	void DrawPercent();

	void Draw();
	void Text();

	void BCollision();

	void SceneChange();

	void Setting(WinApp* winApp);

	void Option_BGMSE_Collision(XMFLOAT2 pos);
	void Option_KEY_Collision(XMFLOAT2 pos);
	void TitleCollision(XMFLOAT2 pos);

	//�}�E�X���W�擾
	POINT mouse_pos;

	XMFLOAT2 lockSize = { 64,64 };

	//���O�𖳂���
	XMFLOAT2 spritePos = { 0,0 };

	XMFLOAT2 cursor_pos = { 0,0 };

	XMFLOAT3 barragePosition[EBULLET_MAX];

	XMFLOAT3 pBPosition[PBULLET_MAX];

	
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
	OptionKey* key = nullptr;



	Object3d* object3d_3 = nullptr;

	//���
	Sprite* yajirusi = nullptr;
	Sprite* yajirusiOp = nullptr;

	XMFLOAT2 yajirusiPos = { 445.0f,465.0f };

	Sprite* opsion_bgmse = nullptr;
	Sprite* opsion_key = nullptr;
	XMFLOAT2 optionPos = { 640,360 };

	XMFLOAT2 mousePos = { 0,0 };

	GameState gameState;

	Sprite* spriteBGMNumber[3];
	Sprite* spriteSENumber[3];
	XMFLOAT2 bgmNumberPos = { 710,210 };
	XMFLOAT2 seNumberPos = { 710,290 };

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

	int count = 0;

	int pHP = 0;

	int eHP = 0;

	//BGM�̉��ʃp�[�Z���g
	int bgmVolume = 100;
	//SE�̉��ʃp�[�Z���g
	int seVolume = 100;


	float volumeSize = 0.01;

	//float bgm = 1.0f;//BGM����
	//float se = 1.0f;//SE����

	LPCSTR hwnd;
};

