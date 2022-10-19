#pragma once
#include"Input.h"
#include"Mouse.h"

using namespace std;
class OptionKey
{	//‰Šú‰»
public:
	void Initialize(Input* input, Mouse* mouse);
	

	void SettingKey();

	int GetLeftKey() { return left; }
	int GetRightKey() { return right; }
	int GetUpKey() { return up; }
	int GetDownKey() { return down; }
	int GetAttackKey() { return attack; }

	int GetCount() { return count; }
	void SetCount(int count) { this->count = count; }
	//10i”æ“¾
	int GetLeftDecimal() { return leftDecimal; }
	int GetRightDecimal() { return rightDecimal; }
	int GetUpDecimaly() { return upDecimal; }
	int GetDownDecimal() { return downDecimal; }
	int GetAttackDecimal() { return attackDecimal; }

private:
	Input* input = nullptr;
	Mouse* mouse = nullptr;
	int left = 0;
	int right = 0;
	int up = 0;
	int down = 0;
	int attack = 0;
	int count = 0;

	//10i”•\¦
	int leftDecimal = 0;
	int rightDecimal = 0;
	int upDecimal = 0;
	int downDecimal = 0;
	int attackDecimal = 0;

};

