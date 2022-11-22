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
		for (int j = 0; j < gameObjects.size(); j++)
		{
			//for文のiとjが同じなら抜け,次のgameObjectへ
			if (i == j)
				continue;

#pragma region 説明用変数ここから
			const XMFLOAT3 axPosition = { gameObjects[i]->GetPosition() };	//オブジェクトAのx成分ポジション
			const XMFLOAT3 ayPosition = { gameObjects[i]->GetPosition() };	//オブジェクトAのy成分ポジション
			const XMFLOAT3 axVelocity = { gameObjects[i]->GetVelocity().x, 0.0f, 0.0f };	//オブジェクトAのx成分移動量
			const XMFLOAT3 ayVelocity = { 0.0f, gameObjects[i]->GetVelocity().y, 0.0f };	//オブジェクトAのy成分移動量
			const float aRadius = gameObjects[i]->GetRadius();	//オブジェクトAの半径
			const bool aPhysicsFlag = gameObjects[i]->GetPhysicsFlag();	//オブジェクトAの物理的判定フラグ
			const XMFLOAT3 velocityXNone = { 0.0f, gameObjects[i]->GetVelocity().y, gameObjects[i]->GetVelocity().z };	//オブジェクトAのx成分移動量を0にする
			const XMFLOAT3 velocityYNone = { gameObjects[i]->GetVelocity().x, 0.0f, gameObjects[i]->GetVelocity().z };	//オブジェクトAのy成分移動量を0にする
			const XMFLOAT3 bxPosition = { gameObjects[i]->GetPosition() };	//オブジェクトBのx成分ポジション
			const XMFLOAT3 byPosition = { gameObjects[i]->GetPosition() };	//オブジェクトBのy成分ポジション
			const float bRadius = gameObjects[i]->GetRadius();	//オブジェクトBの半径
			const bool bPhysicsFlag = gameObjects[i]->GetPhysicsFlag();	//オブジェクトBの物理的判定フラグ
#pragma endregion ここまで

//衝突判定_x成分
			bool hitFlag = false;
			if (((std::powf((axPosition + axVelocity - bxPosition).x, 2.0)) + (std::powf((ayPosition - byPosition).y, 2.0))) <=
				(std::powf(aRadius + bRadius, 2.0)))
			{
				if (aPhysicsFlag && bPhysicsFlag)
				{
					gameObjects[i]->SetVelocity(velocityXNone);
					hitFlag = true;
				}
			}
			//衝突判定_y成分
			if (((std::powf((axPosition - bxPosition).x, 2.0)) + (std::powf((ayPosition + ayVelocity - byPosition).y, 2.0))) <=
				(std::powf(aRadius + bRadius, 2.0)))
			{
				if (aPhysicsFlag && bPhysicsFlag)
				{
					gameObjects[i]->SetVelocity(velocityYNone);
					hitFlag = true;
				}
			}

			if (hitFlag == true)
			{
				gameObjects[i]->SetActionFlag(gameObjects[i]->GetActionFlag());
			}

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
}

	void GameManager::Draw()
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Draw();
		}
	}

	void GameManager::AddGameObject(GameObject * gameObject)
	{
		gameObjects.push_back(gameObject);
	}
