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
	//セーブデータ
	typedef struct {
		int left;//左移動ボタン
		int right;//右移動ボタン
		int up;//上移動ボタン
		int down;//下移動ボタン
		int attack;//攻撃ボタン
		int sensi;//感度
		int drawSensi;//表示用感度
		int bgm;//bgm音量
		int se;//se音量
	}SaveData;


private://エイリアス
//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
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

	//マウス座標取得
	POINT mouse_pos;

	XMFLOAT2 lockSize = { 64,64 };

	//ラグを無くす
	XMFLOAT2 spritePos = { 0,0 };

	XMFLOAT2 cursor_pos = { 0,0 };


private:
	GameManager* gameObjectManager = nullptr;

	//ポインタ置き場
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
	//矢印
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

	//デバックテキスト用
	char str[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];

	int time = 0;

	//スプライト
	const int SPRITE_NUM = 10;
	//Sprite sprite[SPRITE_NUM];

	//デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 0;

	int count = 0;

	int pHP = 0;

	int eHP = 0;

	//BGMの音量パーセント
	int bgmVolume = 100;
	//SEの音量パーセント
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

	//float bgm = 1.0f;//BGM音量
	//float se = 1.0f;//SE音量

	LPCSTR hwnd;


	bool cursorCount = false;

	bool hitFlag = false;
	int flagTime = 0;

	int sceneCount = 0;
};

