#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	std::vector<GameObject*>().swap(gameObjects);
}

void GameManager::Initialize(Input* input, Audio* audio, Mouse* mouse)
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->BaseInitialize(input, audio, mouse, gameObjects);
		gameObject->Initialize();
	}
}

void GameManager::Update()
{
	std::vector<GameObject*> addGameObjects;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();

		gameObjects[i]->referenceGameObjects = gameObjects;

		if (gameObjects[i]->addGameObjects.size() != 0)//追加したいゲームオブジェクトがあれば
		{
			for (GameObject* addGameObject : gameObjects[i]->addGameObjects)
			{
				addGameObjects.push_back(addGameObject);//追加したいオブジェクトを一時的な変数に代入
			}
		}
		std::vector<GameObject*>().swap(gameObjects[i]->addGameObjects);//データの入れ替え
	}

	for (GameObject* addGameObject : addGameObjects)
	{
		AddGameObject(addGameObject);//エラーを防ぐため
	}
	std::vector<GameObject*>().swap(addGameObjects);

	auto it = std::partition(gameObjects.begin(), gameObjects.end(), [](GameObject* gameObject)
		{ return gameObject->GetDeathFlag() == true; });

	std::for_each(gameObjects.begin(), it, [](GameObject* gameObject) {delete gameObject; });
	gameObjects.erase(gameObjects.begin(), it);

}

void GameManager::Draw()
{
	for (GameObject* gameObject : gameObjects)
	{
		gameObject->Draw();
	}
}

void GameManager::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}
