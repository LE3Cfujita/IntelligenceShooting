#include "OptionKey.h"

void OptionKey::Initialize(Input* input, Mouse* mouse)
{
	this->input = input;
	this->mouse = mouse;
}

int OptionKey::SettingKey()
{
	return 0;
}
