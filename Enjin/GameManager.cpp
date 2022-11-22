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
			//for����i��j�������Ȃ甲��,����gameObject��
			if (i == j)
				continue;

#pragma region �����p�ϐ���������
			const XMFLOAT3 axPosition = { gameObjects[i]->GetPosition() };	//�I�u�W�F�N�gA��x�����|�W�V����
			const XMFLOAT3 ayPosition = { gameObjects[i]->GetPosition() };	//�I�u�W�F�N�gA��y�����|�W�V����
			const XMFLOAT3 axVelocity = { gameObjects[i]->GetVelocity().x, 0.0f, 0.0f };	//�I�u�W�F�N�gA��x�����ړ���
			const XMFLOAT3 ayVelocity = { 0.0f, gameObjects[i]->GetVelocity().y, 0.0f };	//�I�u�W�F�N�gA��y�����ړ���
			const float aRadius = gameObjects[i]->GetRadius();	//�I�u�W�F�N�gA�̔��a
			const bool aPhysicsFlag = gameObjects[i]->GetPhysicsFlag();	//�I�u�W�F�N�gA�̕����I����t���O
			const XMFLOAT3 velocityXNone = { 0.0f, gameObjects[i]->GetVelocity().y, gameObjects[i]->GetVelocity().z };	//�I�u�W�F�N�gA��x�����ړ��ʂ�0�ɂ���
			const XMFLOAT3 velocityYNone = { gameObjects[i]->GetVelocity().x, 0.0f, gameObjects[i]->GetVelocity().z };	//�I�u�W�F�N�gA��y�����ړ��ʂ�0�ɂ���
			const XMFLOAT3 bxPosition = { gameObjects[i]->GetPosition() };	//�I�u�W�F�N�gB��x�����|�W�V����
			const XMFLOAT3 byPosition = { gameObjects[i]->GetPosition() };	//�I�u�W�F�N�gB��y�����|�W�V����
			const float bRadius = gameObjects[i]->GetRadius();	//�I�u�W�F�N�gB�̔��a
			const bool bPhysicsFlag = gameObjects[i]->GetPhysicsFlag();	//�I�u�W�F�N�gB�̕����I����t���O
#pragma endregion �����܂�

//�Փ˔���_x����
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
			//�Փ˔���_y����
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

			if (gameObjects[i]->addGameObjects.size() != 0)//�ǉ��������Q�[���I�u�W�F�N�g�������
			{
				for (GameObject* addGameObject : gameObjects[i]->addGameObjects)
				{
					addGameObjects.push_back(addGameObject);//�ǉ��������I�u�W�F�N�g���ꎞ�I�ȕϐ��ɑ��
				}
			}
			std::vector<GameObject*>().swap(gameObjects[i]->addGameObjects);//�f�[�^�̓���ւ�
		}

		for (GameObject* addGameObject : addGameObjects)
		{
			AddGameObject(addGameObject);//�G���[��h������
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
