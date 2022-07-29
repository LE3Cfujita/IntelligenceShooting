#include<windows.h>
#pragma once
class WinApp
{public://静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public://メンバ関数
	//初期化
	void Initialize();
	//更新
	void Update();
	//終了
	void Finalize();
	//メッセージの処理
	bool ProcessMessage();

private:
	//ウィンドウハンドル
	HWND hwnd = nullptr; 

	//ウィンドウクラスの設定
	WNDCLASSEX w{};
public:

	//getter
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return w.hInstance; }

	//静的メンバ変数

//ウィンドウサイズ
	static const int window_width = 1280;  //横幅
	static const int window_height = 720;  //縦幅
};

