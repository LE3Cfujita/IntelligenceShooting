#pragma once
#include"Sprite.h"
#include <string>
class DebugText
{
public: // 定数の宣言    
	static const int maxCharCount = 256;    // 最大文字数
	static const int fontWidth = 9;         // フォント画像内1文字分の横幅
	static const int fontHeight = 18;       // フォント画像内1文字分の縦幅
	static const int fontLineCount = 14;    // フォント画像内1行分の文字数

public: // メンバ関数
	DebugText();
	~DebugText();
	void Initialize( UINT texnumber);

	void Print(const std::string& text, float x, float y, float scale = 1.0f);
	void Print(const std::string& text, float x, float y, float scaleX, float scaleY);

	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private: // メンバ変数     
	// スプライトデータの配列
	Sprite* sprites[maxCharCount]={};
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
};

