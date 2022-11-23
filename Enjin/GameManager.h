#pragma once

#include <algorithm>

#include "Input.h"
#include "Audio.h"
#include"Mouse.h"
#include "GameObject.h"
#include"XMFLOAT_Helper.h"
class GameManager
{
private:
	std::vector<GameObject*> gameObjects;
	Input* input = nullptr;
	Audio* audio = nullptr;
public:

	GameManager();
	~GameManager();
	void Initialize(Input* input, Audio* audio,Mouse*mouse, Collision* collision);
	void Update();
	void Draw();
	void AddGameObject(GameObject* gameObject);
	std::vector<GameObject*> GetGameObjects() { return gameObjects; }
};

