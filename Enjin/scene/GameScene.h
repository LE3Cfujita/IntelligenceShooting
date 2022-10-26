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
#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>
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
		OVER
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

	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio, Mouse* mouse);

	void Update(WinApp* winApp);

	void Title();

	void Option_BGMSE();
	void Option_KEY();
	void Option_Select();
	void Option_Sensi();
	void DrawVolumePercent();
	void DrawSensiPercent();

	void Draw();
	void Text();

	void BCollision();

	void SceneChange();

	void Setting(WinApp* winApp);
	void Option_KEY_Collision(XMFLOAT2 pos);

	void WriteFile();
	void LoadFile();

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
	
	/*Model* ground = nullptr;
	Object3d* woods = nullptr;
	XMFLOAT3 woodsPos = { 0,0,0 };*/

	Object3d* object3d_3 = nullptr;

	//矢印
	Sprite* yajirusi = nullptr;
	Sprite* yajirusiOp = nullptr;

	XMFLOAT2 yajirusiPos = { 445.0f,465.0f };

	Sprite* opsion_Select = nullptr;

	Sprite* opsion_bgmse = nullptr;
	Sprite* opsion_key = nullptr;
	Sprite* opsion_sensi = nullptr;
	XMFLOAT2 optionPos = { 640,360 };

	XMFLOAT2 mousePos = { 0,0 };

	GameState gameState;

	Sprite* spriteBGMNumber[3];
	Sprite* spriteSENumber[3];
	Sprite* spriteSENSINumber[3];
	XMFLOAT2 bgmNumberPos = { 670,200 };
	XMFLOAT2 seNumberPos = { 670,330 };
	XMFLOAT2 sensiNumberPos = { 670,255 };

	Sprite* induction = nullptr;
	XMFLOAT2 indPos = { 640,120 };

	//デバックテキスト用
	char str[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];

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

	int sensi = 0;
	int drawSensi = 70;

	//float bgm = 1.0f;//BGM音量
	//float se = 1.0f;//SE音量

	LPCSTR hwnd;
};

