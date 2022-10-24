#pragma once
#include"Input.h"
#include"Mouse.h"

using namespace std;
class OptionKey
{	//èâä˙âª
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
	//10êiêîéÊìæ
	int GetLeftDecimal() { return leftDecimal; }
	int GetRightDecimal() { return rightDecimal; }
	int GetUpDecimaly() { return upDecimal; }
	int GetDownDecimal() { return downDecimal; }
	int GetAttackDecimal() { return attackDecimal; }

	void SetLeftDecimal(int left) { leftDecimal = left; }
	void SetRightDecimal(int right) { rightDecimal = right; }
	void SetUpDecimaly(int up) { upDecimal = up; }
	void SetDownDecimal(int down) { downDecimal = down; }
	void SetAttackDecimal(int attack) { attackDecimal = attack; }

private:
	Input* input = nullptr;
	Mouse* mouse = nullptr;
	int left = 0;
	int right = 0;
	int up = 0;
	int down = 0;
	int attack = 0;
	int count = 0;

	//10êiêîï\é¶
	int leftDecimal = 0;
	int rightDecimal = 0;
	int upDecimal = 0;
	int downDecimal = 0;
	int attackDecimal = 0;

};

