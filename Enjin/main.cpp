#include "Input.h"
#include"Mouse.h"
#include "WinApp.h"
#include"DirectXCommon.h"
#include"Sprite.h"
#include "DebugText.h"
#include"Audio.h"
#include"GameScene.h"
#include<chrono>

//# Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#pragma region WindowsAPI初期化処理
	srand((unsigned int)time(NULL));

	//ポインタ置き場
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Mouse* mouse = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Sprite* sprite = nullptr;
	GameScene* gameScene = nullptr;

	winApp = new WinApp();
	winApp->Initialize();
	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initislize(winApp);
	
	//入力の初期化
	input = Input::GetInstance();
	if (!input->Initialize(winApp->GetHInstance(), winApp->GetHwnd())) {
		assert(0);
		return 1;
	}

	mouse = Mouse::GetInstance();
	if (!mouse->Initialize(winApp->GetHInstance(), winApp->GetHwnd())) {
		assert(0);
		return 1;
	}


	//音声の初期化
	audio = new Audio();
	audio->Initialize();

	//スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDev(), winApp->window_width, winApp->window_height);
	//3dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);


	gameScene = new GameScene();
	gameScene->Initialize(dxCommon,audio,input,mouse);


	while (input->TriggerKey(DIK_ESCAPE) == 0)  //ゲームループ
	{
#pragma region ウィンドウメッセージ処理
		//windowsのメッセージ処理
		if (winApp->ProcessMessage())
		{
			//ゲームループを抜ける
			break;
		}
		input->Update();
		mouse->Update();

		gameScene->Update(winApp);

		dxCommon->PreDraw();

		gameScene->Draw();

		dxCommon->PostDraw();
	}
	gameScene->WriteFile();
	safe_delete(gameScene);

	//DirectXの解放
	//safe_delete(dxCommon);
	// 音声データ解放
	audio->SoundUnload();
	// XAudio2解放
	safe_delete(audio);

#pragma region WindowsAPI後始末
	//ウィンドウクラスを登録解除
	winApp->Finalize();

	//WindowsAPI解放
	safe_delete(winApp);
#pragma endregion WindowsAPI後始末

	return 0;
}

