#pragma once
#include"Input.h"
#include"Mouse.h"
class OptionKey
{	//‰Šú‰»
public:
	void Initialize(Input* input, Mouse* mouse);

	int SettingKey();

private:
	Input* input = nullptr;
	Mouse* mouse = nullptr;
};

