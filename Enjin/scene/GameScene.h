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

#include <DirectXMath.h>
#pragma once
class GameScene
{
private://エイリアス
//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio, Mouse* mouse);

	void Update(WinApp* winApp);

	void Draw();
	void Text();

	void Delete();


	//マウス座標取得
	POINT mouse_pos;

	XMFLOAT2 lockSize = { 64,64 };

	//ラグを無くす
	XMFLOAT2 spritePos = { 0,0 };

	XMFLOAT2 cursor_pos = { 0,0 };

	int count = 0;

private:


	//ポインタ置き場
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Sprite* sprite = nullptr;
	DebugCamera* camera = nullptr;


	//FBX宣言
	ModelFBX* model = nullptr;

	ObjectFBX* object = nullptr;


	//Obj宣言
	Model* modelGround = nullptr;
	Model* modelPlayer = nullptr;

	//3Dオブジェクト生成
	Object3d* ground = nullptr;
	Object3d* player = nullptr;
	Object3d* object3d_3 = nullptr;



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
};

