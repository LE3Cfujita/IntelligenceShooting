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

	//マウス座標取得
	POINT mouse_pos;

	XMFLOAT2 lockSize = { 64,64 };

	//ラグを無くす
	XMFLOAT2 spritePos = { 0,0 };

	XMFLOAT2 cursor_pos = { 0,0 };

	XMFLOAT3 barragePosition[EBULLET_MAX];

	XMFLOAT3 pBPosition[PBULLET_MAX];

	
private:


	//ポインタ置き場
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

	//矢印
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

	//デバックテキスト用
	char str[100];
	char str2[100];
	char str3[100];
	char str4[100];

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


	float volumeSize = 0.01;

	//float bgm = 1.0f;//BGM音量
	//float se = 1.0f;//SE音量

	LPCSTR hwnd;
};

