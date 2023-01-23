#include"Sprite.h"
#include "DebugText.h"
#include"DirectXCommon.h"
#include"DebugCamera.h"
#include"Player.h"
#include"PlayerBullet.h"
#include"Enemy.h"
#include"OptionKey.h"
#include"GameManager.h"
#include"Rock.h"
#include"Star.h"
#include"Efect.h"
#pragma once

class GameScene
{
public:
	enum GameState
	{
		TITLE,
		OPTION_SELECT,
		OPTION_SOUND,
		OPTION_KEY,
		OPTION_SENSI,
		PLAY,
		CLEA,
		OVER,
		SCENECHANGE,
		SCENECHANGEOVER,
		SCENECHANGECLEA,
		OPERATION,
		RULE
	};
	//�Z�[�u�f�[�^
	typedef struct {
		int left;//���ړ��{�^��
		int right;//�E�ړ��{�^��
		int up;//��ړ��{�^��
		int down;//���ړ��{�^��
		int attack;//�U���{�^��
		int sensi;//���x
		int drawSensi;//�\���p���x
		int bgm;//bgm����
		int se;//se����
	}SaveData;


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

	void Initialize(DirectXCommon* dxCommon, Audio* audio, Input* input, Mouse* mouse);

	void SpriteCreate();

	void ObjInitialize();

	void Update(WinApp* winApp);

	void ObjCollision();


	void CreateStars();

	void Title();

	void Option_BGMSE();
	void Option_KEY();
	void Option_Select();
	void Option_Sensi();
	void DrawVolumePercent();
	void DrawSensiPercent();

	void Draw();
	void Text();


	void SceneChange();

	void Setting(WinApp* winApp);
	void Option_KEY_Collision(XMFLOAT2 pos);

	void WriteFile();
	void LoadFile();

	void HitEfect(XMFLOAT3 pos);

	void ChangeScene(int count);

	//�}�E�X���W�擾
	POINT mouse_pos;

	XMFLOAT2 lockSize = { 64,64 };

	//���O�𖳂���
	XMFLOAT2 spritePos = { 0,0 };

	XMFLOAT2 cursor_pos = { 0,0 };


private:
	GameManager* gameObjectManager = nullptr;

	//�|�C���^�u����
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Sprite* sprite = nullptr;
	Mouse* mouse = nullptr;
	Collision* collision = nullptr;
	OptionKey* key = nullptr;
	Enemy* enemy = nullptr;
	Player* player = nullptr;
	EnemyBarrage* barrage = nullptr;
	//���
	Sprite* yajirusi = nullptr;
	Sprite* yajirusiOp = nullptr;
	Sprite* spriteBGMNumber[3];
	Sprite* spriteSENumber[3];
	Sprite* spriteSENSINumber[3];
	Sprite* induction = nullptr;
	Sprite* opsion_bgmse = nullptr;
	Sprite* opsion_key = nullptr;
	Sprite* opsion_sensi = nullptr;
	Sprite* clear = nullptr;
	Sprite* over = nullptr;
	Sprite* HPback = nullptr;
	Sprite* HPber = nullptr;
	Sprite* sceneSprite = nullptr;
	Rock* rock = nullptr;

	Model* dome = nullptr;
	Object3d* skydome = nullptr;
	XMFLOAT3 skyrot = { 0,0,0 };


	XMFLOAT2 yajirusiPos = { 315.0f,435.0f };

	Sprite* opsion_Select = nullptr;


	XMFLOAT2 optionPos = { 640,360 };

	XMFLOAT2 mousePos = { 0,0 };

	GameState gameState;

	XMFLOAT2 bgmNumberPos = { 670,200 };
	XMFLOAT2 seNumberPos = { 670,330 };
	XMFLOAT2 sensiNumberPos = { 670,255 };

	XMFLOAT2 indPos = { 640,120 };

	XMFLOAT2 hpsize = { 250,25 };

	XMFLOAT2 scenePos = { 640.0f,360.0f };
	XMFLOAT2 sceneSize = { 0.1f,0.1f };

	//�f�o�b�N�e�L�X�g�p
	char str[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];

	int time = 0;

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

	int keyCount = 0;

	float volumeSize = 0.01;


	int left = 0;
	int right = 0;
	int up = 0;
	int down = 0;
	int attack = 0;

	int sensi = 5;
	int drawSensi = 70;

	int sceneChangeFlag = false;

	//float bgm = 1.0f;//BGM����
	//float se = 1.0f;//SE����

	LPCSTR hwnd;


	bool cursorCount = false;

	bool hitFlag = false;
	int flagTime = 0;

	int sceneCount = 0;
};

