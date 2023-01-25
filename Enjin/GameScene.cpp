#include "GameScene.h"
#include "Model.h"
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(key);
	safe_delete(collision);
	safe_delete(sprite);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Audio* audio, Input* input, Mouse* mouse)
{
	this->dxCommon = dxCommon;
	this->audio = audio;
	this->input = input;
	this->mouse = mouse;

	gameState = GameState::TITLE;
	gameObjectManager = new GameManager();
	gameObjectManager->Initialize(input, audio, mouse, collision);


	SpriteCreate();
	player = new Player();
	player->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
	player->Initialize();
	pHP = player->GetHP();
	gameObjectManager->AddGameObject(player);
	ObjInitialize();





	left = key->GetLeftDecimal();
	right = key->GetRightDecimal();
	up = key->GetUpDecimaly();
	down = key->GetDownDecimal();
	attack = key->GetAttackDecimal();




	LoadFile();
	audio->SoundLoadWave("Alarm01.wav", 0);//テスト
	audio->SoundLoadWave("decisionSE.wav", 1);//テスト
	audio->SoundVolume(0, bgmVolume * volumeSize);
	audio->SoundVolume(1, seVolume * volumeSize);
	audio->SoundPlayWave("Alarm01.wav", true);



}

void GameScene::SpriteCreate()
{
	//デバッグテキスト用のテクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	//デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	sprite->LoadTexture(2, L"Resources/title.png");

	sprite = Sprite::Create(2, { 0.0f,0.0f });

	// テクスチャ読み込み
	yajirusi->LoadTexture(3, L"Resources/yazirusi.png");
	yajirusiOp->LoadTexture(3, L"Resources/yazirusi.png");

	yajirusi = Sprite::Create(3, yajirusiPos);
	yajirusiOp = Sprite::Create(3, { 450,185 });

	// テクスチャ読み込み
	opsion_bgmse->LoadTexture(4, L"Resources/BGMSEOpsion.png");

	opsion_bgmse = Sprite::Create(4, optionPos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	opsion_bgmse->SetSize({ 500,420 });

	opsion_key->LoadTexture(6, L"Resources/OPTION_KEY.png");

	opsion_key = Sprite::Create(6, optionPos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	opsion_key->SetSize({ 720,360 });

	induction->LoadTexture(7, L"Resources/induction.png");

	induction = Sprite::Create(7, indPos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	induction->SetSize({ 720,100 });

	opsion_Select->LoadTexture(8, L"Resources/OPTIONSelect.png");

	opsion_Select = Sprite::Create(8, optionPos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	opsion_Select->SetSize({ 420,420 });

	opsion_sensi->LoadTexture(9, L"Resources/Sensi.png");

	opsion_sensi = Sprite::Create(9, optionPos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	opsion_sensi->SetSize({ 500,420 });

	if (!Sprite::LoadTexture(5, L"Resources/number.png")) {
		assert(0);
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		spriteBGMNumber[i] = Sprite::Create(5, { (float)(i * 26 + 300),370 });
		spriteSENumber[i] = Sprite::Create(5, { (float)(i * 26 + 300),370 });
		spriteSENSINumber[i] = Sprite::Create(5, { (float)(i * 26 + 300),370 });
	}



	sceneSprite->LoadTexture(14, L"Resources/Scene.png");
	sceneSprite = Sprite::Create(14, scenePos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	sceneSprite->SetSize(sceneSize);
	sceneSprite->SetPosition(scenePos);

	operation->LoadTexture(15, L"Resources/operation.png");
	operation = Sprite::Create(15, { 0.0f,0.0f });
	operation->SetPosition({ 0,0 });
	rule->LoadTexture(16, L"Resources/rule.png");
	rule = Sprite::Create(16, { 0.0f,0.0f });
	rule->SetPosition({ 1280,0 });

	Model::AdvanceLoadModel(1, "enemyBullet");
	Model::AdvanceLoadModel(2, "bullet2");
	Model::AdvanceLoadModel(3, "planet");
	Model::AdvanceLoadModel(4, "player");
	Model::AdvanceLoadModel(5, "enemy");
	Model::AdvanceLoadModel(6, "rocket");
	Model::AdvanceLoadModel(7, "normal");
	Model::AdvanceLoadModel(8, "shield");
	Model::AdvanceLoadModel(9, "efect");
	Model::AdvanceLoadModel(10, "enemyBullet");
	Model::AdvanceLoadModel(11, "skydome");
}

void GameScene::ObjInitialize()
{
	rock = new Rock();
	rock->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
	rock->Initialize();
	gameObjectManager->AddGameObject(rock);

	key = new OptionKey();
	key->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
	key->Initialize();
	gameObjectManager->AddGameObject(key);

	dome = Model::CreateModel(11);
	skydome = Object3d::Create();
	skydome->SetModel(dome);
	skydome->SetScale({ 3,3,3 });
	skydome->SetPosition({ 0,0,100 });
}

void GameScene::Update(WinApp* winApp)
{
	winApp->GetHwnd();

	Setting(winApp);
	//Text();


	switch (gameState)
	{
	case GameState::TITLE://タイトル
		Title();
		break;
	case GameState::OPTION_SELECT:
		Option_Select();
		break;
	case GameState::OPTION_SOUND://操作説明など
		Option_BGMSE();
		break;
	case GameState::OPTION_KEY:
		Option_KEY();
		break;
	case GameState::OPTION_SENSI:
		Option_Sensi();
		break;
	case GameState::PLAY://ゲームシーン
		ObjCollision();
		SceneChange();

		CreateStars();

		if (hitFlag == true)
		{
			flagTime++;
			if (flagTime >= 120)
			{
				hitFlag = false;
				flagTime = 0;
			}
		}

		SetCursorPos(690, 360);

		gameObjectManager->Update();
		break;
	case GameState::OVER://ゲームオーバー
		if (mousePos.x >= 440 &&
			mousePos.x <= 840 &&
			mousePos.y >= 470 &&
			mousePos.y <= 550)
		{
			if (mouse->TriggerMouseLeft())
			{

				sceneCount = 2;
				gameState = GameState::SCENECHANGEOVER;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
				cursorCount = false;
				sceneChangeFlag = false;
			}
		}
		break;

	case GameState::CLEA://ゲームクリア
		if (mousePos.x >= 440 &&
			mousePos.x <= 840 &&
			mousePos.y >= 470 &&
			mousePos.y <= 550)
		{
			if (mouse->TriggerMouseLeft())
			{

				sceneCount = 2;
				gameState = GameState::SCENECHANGECLEA;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
				cursorCount = false;
				sceneChangeFlag = false;
			}
		}
		break;
	case GameState::SCENECHANGE://シーン切り替え
		ChangeScene(sceneCount);
		break;
	case GameState::SCENECHANGEOVER://シーン切り替え
		ChangeScene(sceneCount);
		break;
	case GameState::SCENECHANGECLEA://シーン切り替え
		ChangeScene(sceneCount);
		break;
	case GameState::OPERATION:
		OperationChange();
		break;
	case GameState::RULE:
		ruleChange();
		break;
	}
	skydome->SetRotation(skyrot);
	skydome->Update();
	mouse->Update();
}

void GameScene::Title()
{
	if (mousePos.x >= 380 && mousePos.x <= 880)
	{
		if (mousePos.y >= 400.0f && mousePos.y <= 500.0f)
		{
			yajirusiPos.y = 435.0f;
			if (mouse->TriggerMouseLeft())
			{
				audio->SoundPlayWave("decisionSE.wav", false);
				ShowCursor(FALSE);
				sceneChangeFlag = false;
				sceneCount = 3;
				operationPos = { 0,0 };
				rulePos = { 1280,0 };
				gameState = GameState::SCENECHANGE;
			}
		}
		if (mousePos.y >= 550.0f && mousePos.y <= 640.0f)
		{
			yajirusiPos.y = 570.0f;
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SELECT;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	yajirusi->SetPosition(yajirusiPos);
}

void GameScene::ObjCollision()
{
	for (GameObject* gameobject : gameObjectManager->GetGameObjects())
	{
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::PLAYER && gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::PLAYERBULLET && gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::EFECT)
		{
			if (collision->ballToball(player->GetPosition(), gameobject->GetPosition(), player->GetRadius(), gameobject->GetRadius()))
			{
				if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::ENEMY)
				{
					player->Hit();
					gameobject->Hit();
					HitEfect(player->GetPosition());
				}
				else
				{
					if (gameobject->GetAttackFlag3() == 1 && player->GetRushCount() == 0)
					{
						player->RushHit();
						HitEfect(player->GetPosition());
					}
				}
				pHP = player->GetHP();
			}
		}
		if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::PLAYERBULLET)continue;
		for (GameObject* gameobject2 : gameObjectManager->GetGameObjects())
		{
			if (gameobject2->GetObjectMember() != GameObject::OBJECTMEMBER::ENEMY && gameobject2->GetObjectMember() != GameObject::OBJECTMEMBER::NORMALENEMY)continue;
			if (collision->ballToball(gameobject->GetPosition(), gameobject2->GetPosition(), gameobject2->GetRadius(), gameobject2->GetRadius()))
			{
				gameobject->Hit();
				gameobject2->Hit();
				if (hitFlag == false)
				{
					HitEfect(gameobject2->GetPosition());
					hitFlag = true;
				}
			}
			eHP = enemy->GetHP();
		}
	}
}


void GameScene::Option_Select()
{
	if (mousePos.x >= 515 && mousePos.x <= 770)
	{
		if (mousePos.y >= 185 && mousePos.y <= 245)
		{
			yajirusiOp->SetPosition({ 450,185 });
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SOUND;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		if (mousePos.y >= 280 && mousePos.y <= 340)
		{
			yajirusiOp->SetPosition({ 450,280 });
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_KEY;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		if (mousePos.y >= 375 && mousePos.y <= 430)
		{
			yajirusiOp->SetPosition({ 450,375 });
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SENSI;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		if (mousePos.y >= 465 && mousePos.y <= 525)
		{
			yajirusiOp->SetPosition({ 450,465 });
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::TITLE;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
}
void GameScene::Option_BGMSE()
{
	if (mousePos.x >= 470 && mousePos.x <= 835)
	{
		if (mousePos.y >= 185 && mousePos.y <= 260)
		{
			yajirusiOp->SetPosition({ 410,200 });
			if (mouse->TriggerMouseLeft())
			{
				if (bgmVolume != 100)
				{
					bgmVolume += 10;
				}
				else
				{
					bgmVolume = 0;
				}
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}

		}
		if (mousePos.y >= 320 && mousePos.y <= 390)
		{
			yajirusiOp->SetPosition({ 410,330 });
			if (mouse->TriggerMouseLeft())
			{
				if (seVolume != 100)
				{
					seVolume += 10;
				}
				else
				{
					seVolume = 0;
				}
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		if (mousePos.y >= 450 && mousePos.y <= 520)
		{
			yajirusiOp->SetPosition({ 410,460 });
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SELECT;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
				yajirusiOp->SetPosition({ 450,185 });
			}
		}
	}
	if (mouse->TriggerMouseRight())
	{
		gameState = GameState::TITLE;
		audio->SoundStop("decisionSE.wav");
		audio->SoundPlayWave("decisionSE.wav", false);
	}
	audio->SoundVolume(0, bgmVolume * volumeSize);
	audio->SoundVolume(1, seVolume * volumeSize);
}


void GameScene::Option_KEY()
{
	Option_KEY_Collision(mousePos);


	if (left != 32)
	{
		sprintf_s(str, "%c", left);
		debugText.Print(str, 555, 320, 3);
	}
	else
	{
		debugText.Print("SPACE", 535, 320, 1.5, 3);
	}
	if (down != 32)
	{
		sprintf_s(str2, "%c", down);
		debugText.Print(str2, 880, 200, 3);
	}
	else
	{
		debugText.Print("SPACE", 860, 200, 1.5, 3);
	}
	if (up != 32)
	{
		sprintf_s(str3, "%c", up);
		debugText.Print(str3, 555, 200, 3);
	}
	else
	{
		debugText.Print("SPACE", 535, 200, 1.5, 3);
	}
	if (right != 32)
	{
		sprintf_s(str4, "%c", right);
		debugText.Print(str4, 880, 320, 3);
	}
	else
	{
		debugText.Print("SPACE", 860, 320, 1.5, 3);
	}
	if (attack != 32)
	{
		sprintf_s(str5, "%c", attack);
		debugText.Print(str5, 650, 430, 3);
	}
	else
	{
		debugText.Print("SPACE", 630, 435, 1.5, 3);
	}
}

void GameScene::CreateStars()
{

	if (time == 0)
	{
		Star* star = new Star();
		star->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
		star->Initialize();
		star->Create();
		gameObjectManager->AddGameObject(star);
		time = 1;
	}
	else
	{
		time++;
		if (time >= 30)
		{
			time = 0;
		}
	}
	skyrot.y += 0.05;
}

void GameScene::DrawVolumePercent()
{
	//BGM
	/*************************/
	//各桁の値を取り出す
	char eachBGMNumber[3] = {};//各桁の値
	int bgmNumber = bgmVolume;//表示する数字

	if (bgmVolume == 100)
	{
		int keta = 100;//最初の桁
		for (int i = 0; i < 3; i++)
		{
			eachBGMNumber[i] = bgmNumber / keta;//今の桁の値を求める
			bgmNumber = bgmNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 3; i++)
		{
			spriteBGMNumber[i]->SetSize({ 32,48 });
			spriteBGMNumber[i]->SetTextureRect({ (float)(32 * eachBGMNumber[i]), 0, }, { 32,32 });
			spriteBGMNumber[i]->SetPosition(XMFLOAT2{ bgmNumberPos.x + i * 32.0f, bgmNumberPos.y }
			);
			spriteBGMNumber[i]->Draw();
		}
	}
	else
	{
		int keta = 10;
		for (int i = 0; i < 2; i++)
		{
			eachBGMNumber[i] = bgmNumber / keta;//今の桁の値を求める
			bgmNumber = bgmNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 2; i++)
		{
			spriteBGMNumber[i]->SetSize({ 32,48 });
			spriteBGMNumber[i]->SetTextureRect({ (float)(32 * eachBGMNumber[i]), 0, }, { 32,32 });
			spriteBGMNumber[i]->SetPosition(XMFLOAT2{ bgmNumberPos.x + 32 + i * 32.0f, bgmNumberPos.y });
			spriteBGMNumber[i]->Draw();
		}
	}
	/**************************/
	//SE
	/**************************/
	//各桁の値を取り出す
	char eachSENumber[3] = {};//各桁の値
	int seNumber = seVolume;//表示する数字

	if (seVolume == 100)
	{
		int keta = 100;//最初の桁
		for (int i = 0; i < 3; i++)
		{
			eachSENumber[i] = seNumber / keta;//今の桁の値を求める
			seNumber = seNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 3; i++)
		{
			spriteSENumber[i]->SetSize({ 32,48 });
			spriteSENumber[i]->SetTextureRect({ (float)(32 * eachSENumber[i]), 0, }, { 32,32 });
			spriteSENumber[i]->SetPosition(XMFLOAT2{ seNumberPos.x + i * 32.0f, seNumberPos.y });
			spriteSENumber[i]->Draw();
		}
	}
	else
	{
		int keta = 10;
		for (int i = 0; i < 2; i++)
		{
			eachSENumber[i] = seNumber / keta;//今の桁の値を求める
			seNumber = seNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 2; i++)
		{
			spriteSENumber[i]->SetSize({ 32,48 });
			spriteSENumber[i]->SetTextureRect({ (float)(32 * eachSENumber[i]), 0, }, { 32,32 });
			spriteSENumber[i]->SetPosition(XMFLOAT2{ seNumberPos.x + 32 + i * 32.0f, seNumberPos.y });
			spriteSENumber[i]->Draw();
		}
	}
	/***************************/
}

void GameScene::DrawSensiPercent()
{

	char eachSensiNumber[3] = {};//各桁の値	
	int sensiNumber = rock->GetDrawSensi();//表示する数字
	if (rock->GetDrawSensi() == 100)
	{
		int keta = 100;//最初の桁
		for (int i = 0; i < 3; i++)
		{
			eachSensiNumber[i] = sensiNumber / keta;//今の桁の値を求める
			sensiNumber = sensiNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 3; i++)
		{
			spriteSENSINumber[i]->SetSize({ 32,48 });
			spriteSENSINumber[i]->SetTextureRect({ (float)(32 * eachSensiNumber[i]), 0, }, { 32,32 });
			spriteSENSINumber[i]->SetPosition(XMFLOAT2{ sensiNumberPos.x + i * 32.0f, sensiNumberPos.y });
			spriteSENSINumber[i]->Draw();
		}
	}
	else if (rock->GetDrawSensi() == 1)
	{
		int keta = 1;
		for (int i = 0; i < 1; i++)
		{
			eachSensiNumber[i] = sensiNumber / keta;//今の桁の値を求める
			sensiNumber = sensiNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 1; i++)
		{
			spriteSENSINumber[i]->SetSize({ 32,48 });
			spriteSENSINumber[i]->SetTextureRect({ (float)(32 * eachSensiNumber[i]), 0, }, { 32,32 });
			spriteSENSINumber[i]->SetPosition(XMFLOAT2{ sensiNumberPos.x + 64 + i * 32.0f, sensiNumberPos.y });
			spriteSENSINumber[i]->Draw();
		}
	}
	else
	{
		int keta = 10;
		for (int i = 0; i < 2; i++)
		{
			eachSensiNumber[i] = sensiNumber / keta;//今の桁の値を求める
			sensiNumber = sensiNumber % keta;//次の桁以下の値を取り出す
			keta = keta / 10;//桁を進める
		}

		for (int i = 0; i < 2; i++)
		{
			spriteSENSINumber[i]->SetSize({ 32,48 });
			spriteSENSINumber[i]->SetTextureRect({ (float)(32 * eachSensiNumber[i]), 0, }, { 32,32 });
			spriteSENSINumber[i]->SetPosition(XMFLOAT2{ sensiNumberPos.x + 32 + i * 32.0f, sensiNumberPos.y });
			spriteSENSINumber[i]->Draw();
		}
	}
}
void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();


	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());


	switch (gameState)
	{
	case GameState::TITLE://タイトル
		break;
	case GameState::OPTION_SELECT:
		break;
	case GameState::OPTION_SOUND://操作説明など
		break;
	case GameState::OPTION_KEY://操作説明など
		break;
	case GameState::PLAY://ゲームシーン
		//3Dオブジェクトの描画
		skydome->SetRotation(skyrot);
		skydome->Update();
		skydome->Draw();
		gameObjectManager->Draw();
		break;
	case GameState::OVER://ゲームオーバー
		break;
	case GameState::CLEA://ゲームクリア
		break;
	case GameState::SCENECHANGE:
	{
		if (sceneChangeFlag == true)
		{
			if (sceneCount == 1)
			{
				skydome->Draw();
				gameObjectManager->Draw();
			}
		}
		break;
	}
	}

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	Sprite::PreDraw(cmdList);

	switch (gameState)
	{
	case GameState::TITLE://タイトル
		sprite->Draw();
		yajirusi->Draw();
		break;
	case GameState::OPTION_SELECT:
		sprite->Draw();
		yajirusi->Draw();
		opsion_Select->Draw();
		yajirusiOp->Draw();
		break;
	case GameState::OPTION_SOUND://操作説明など
		sprite->Draw();
		yajirusi->Draw();
		opsion_bgmse->Draw();
		yajirusiOp->Draw();
		DrawVolumePercent();
		break;
	case GameState::OPTION_KEY://操作説明など
		sprite->Draw();
		yajirusi->Draw();
		opsion_key->Draw();
		if (keyCount != 0)
		{
			induction->Draw();
		}
		break;
	case GameState::OPTION_SENSI:
		sprite->Draw();
		yajirusi->Draw();
		opsion_sensi->Draw();
		DrawSensiPercent();
		break;
	case GameState::PLAY://ゲームシーン
		HPback->Draw();
		hpsize.x = player->GetHP();
		HPber->SetSize(hpsize);
		HPber->Draw();
		break;
	case GameState::OVER://ゲームオーバー
		over->Draw();
		break;
	case GameState::CLEA://ゲームクリア
		clear->Draw();
		break;
	case GameState::SCENECHANGE:
		operation->SetPosition(operationPos);
		rule->SetPosition(rulePos);
		if (sceneChangeFlag == false)
		{
			if (sceneCount == 1)
			{
				rule->Draw();
			}
			else if (sceneCount == 3)
			{
				sprite->Draw();
				yajirusi->Draw();
			}
			else if (sceneCount == 4)
			{
				operation->Draw();
			}
		}
		else
		{
			if (sceneCount == 1)
			{
				HPback->Draw();
				hpsize.x = player->GetHP();
				HPber->SetSize(hpsize);
				HPber->Draw();
			}
			if (sceneCount == 3)
			{
				operation->Draw();
			}
			else if (sceneCount == 4)
			{
				sprite->Draw();
				yajirusi->Draw();
			}
		}
		sceneSprite->SetSize(sceneSize);
		sceneSprite->Draw();
		break;
	case GameState::SCENECHANGEOVER:

		if (sceneChangeFlag == true)
		{
			sprite->Draw();
			yajirusi->Draw();
		}
		else
		{
			over->Draw();
		}
		sceneSprite->SetSize(sceneSize);
		sceneSprite->Draw();
		break;
	case GameState::SCENECHANGECLEA:

		if (sceneChangeFlag == true)
		{
			sprite->Draw();
			yajirusi->Draw();
		}
		else
		{
			clear->Draw();
		}
		sceneSprite->SetSize(sceneSize);
		sceneSprite->Draw();
		break;
	case GameState::OPERATION:

		operation->SetPosition(operationPos);
		rule->SetPosition(rulePos);
		operation->Draw();
		if (operationCount == true)
		{
			rule->Draw();
		}
		sceneSprite->SetSize(sceneSize);
		if (sceneSize.x > 0 && sceneSize.y > 0)
		{
			sceneSprite->Draw();
		}
		break;
	case GameState::RULE:
		operation->SetPosition(operationPos);
		rule->SetPosition(rulePos);
		if (operationCount == true)
		{
			operation->Draw();
		}
		rule->Draw();
		sceneSprite->SetSize(sceneSize);
		if (sceneSize.x > 0 && sceneSize.y > 0)
		{
			sceneSprite->Draw();
		}
		break;
	}
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	Sprite::PostDraw();
}

void GameScene::Option_Sensi()
{
	if (mousePos.x >= 440 && mousePos.x <= 850)
	{
		if (mousePos.y >= 245 && mousePos.y <= 320)
		{
			if (mouse->TriggerMouseLeft())
			{
				rock->SetSensi(rock->GetSensi() + 10, rock->GetDrawSensi() - 10);
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	if (mousePos.x >= 520 && mousePos.x <= 755)
	{
		if (mousePos.y >= 460 && mousePos.y <= 530)
		{
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SELECT;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	if (mouse->TriggerMouseRight())
	{
		gameState = GameState::TITLE;
		audio->SoundStop("decisionSE.wav");
		audio->SoundPlayWave("decisionSE.wav", false);
	}
}

void GameScene::Text()
{
	int HP = 0;
	for (GameObject* gameobject : gameObjectManager->GetGameObjects())
	{
		if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::PLAYER)
		{
			HP = gameobject->GetHP();
		}
		if (gameobject->GetObjectMember() == GameObject::OBJECTMEMBER::ENEMY)
		{
			eHP = gameobject->GetHP();
		}
	}
	sprintf_s(str, "x = %f", mousePos.x);
	debugText.Print(str, 0, 0, 1);
	sprintf_s(str2, "y = %f", mousePos.y);
	debugText.Print(str2, 0, 20, 1);
}


void GameScene::SceneChange()
{

	if (pHP <= 0)
	{
		if (cursorCount == false)
		{
			ShowCursor(TRUE);
			cursorCount = true;
		}
		gameState = GameState::OVER;//ゲームオーバー
	}
	if (eHP <= 0)
	{
		if (cursorCount == false)
		{
			ShowCursor(TRUE);
			cursorCount = true;
		}
		gameState = GameState::CLEA;//ゲームクリア
	}
}

void GameScene::Setting(WinApp* winApp)
{
	// マウス座標を取得する
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(winApp->GetHwnd(), &p);

	mousePos = { (float)p.x,(float)p.y };
}


void GameScene::Option_KEY_Collision(XMFLOAT2 pos)
{
	if (pos.x >= 523 && pos.x <= 610)
	{
		//うえ
		if (pos.y >= 198 && pos.y <= 258)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(1);
				keyCount = 1;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		//ひだり
		if (pos.y >= 317 && pos.y <= 375)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(2);
				keyCount = 2;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	if (pos.x >= 845 && pos.x <= 940)
	{

		//した
		if (pos.y >= 198 && pos.y <= 258)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(3);
				keyCount = 3;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		//みぎ
		if (pos.y >= 317 && pos.y <= 375)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(4);
				keyCount = 4;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	//攻撃
	if (pos.x >= 586 && pos.x <= 743)
	{
		if (pos.y >= 430 && pos.y <= 490)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(5);
				keyCount = 5;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	if (pos.x >= 835 && pos.x <= 1000)
	{
		if (pos.y >= 495 && pos.y <= 530)
		{
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SELECT;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
				yajirusiOp->SetPosition({ 450,185 });
			}
		}
	}
	if (mouse->TriggerMouseRight())
	{
		gameState = GameState::TITLE;
		audio->SoundStop("decisionSE.wav");
		audio->SoundPlayWave("decisionSE.wav", false);
	}
	if (keyCount != 0)
	{
		key->SettingKey();
		keyCount = key->GetKeyCount();
		player->GetKey();
		left = key->GetLeftDecimal();
		right = key->GetRightDecimal();
		up = key->GetUpDecimaly();
		down = key->GetDownDecimal();
		attack = key->GetAttackDecimal();
	}
}


void GameScene::WriteFile()
{
	sensi = rock->GetSensi();
	drawSensi = rock->GetDrawSensi();
	SaveData Data = { left,right,up,down,attack,sensi,drawSensi,bgmVolume,seVolume };
	FILE* fp;
	fopen_s(&fp, "save.pdf", "w");
	fwrite(&Data, sizeof(Data), 2, fp);
	fclose(fp);
}

void GameScene::LoadFile()
{

	SaveData Data;
	FILE* fp;
	fopen_s(&fp, "save.pdf", "r");
	if (fp != NULL)
	{
		fread(&Data, sizeof(Data), 1, fp);
		fclose(fp);
		left = Data.left;
		right = Data.right;
		up = Data.up;
		down = Data.down;
		attack = Data.attack;

		bgmVolume = Data.bgm;
		seVolume = Data.se;

		key->SetLeftDecimal(left);
		key->SetRightDecimal(right);
		key->SetUpDecimaly(up);
		key->SetDownDecimal(down);
		key->SetAttackDecimal(attack);
		player->referenceGameObjects = gameObjectManager->GetGameObjects();
		player->GetKey();
		rock->SetSensi(Data.sensi, Data.drawSensi);
		sensi = Data.sensi;
		drawSensi = Data.drawSensi;
	}
}

void GameScene::HitEfect(XMFLOAT3 pos)
{
	for (int i = 0; i < 3; i++)
	{
		Efect* efect = new Efect();
		efect->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
		efect->Initialize(pos);
		efect->Create(i);
		gameObjectManager->AddGameObject(efect);
	}
}

void GameScene::ChangeScene(int count)
{
	if (count == 1)
	{
		if (sceneSize.x >= 1280 && sceneSize.y >= 720)
		{
			sceneChangeFlag = true;
			enemy = new Enemy();
			enemy->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
			enemy->Initialize();
			eHP = enemy->GetHP();
			gameObjectManager->AddGameObject(enemy);

			if (spriteCount == false)
			{
				PlaySprite();
			}
		}
		if (sceneChangeFlag == false)
		{
			sceneSize.x += 8;
			sceneSize.y += 4.5;
		}
		else
		{
			sceneSize.x -= 8;
			sceneSize.y -= 4.5;
			if (sceneSize.x < 0 && sceneSize.y < 0)
			{
				gameState = GameState::PLAY;
			}
		}
	}
	else if (count == 2|| count == 4)
	{

		if (sceneSize.x >= 1280 && sceneSize.y >= 720)
		{
			for (GameObject* gameobject : gameObjectManager->GetGameObjects())
			{
				if (gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::OPTIONKEY && gameobject->GetObjectMember() != GameObject::OBJECTMEMBER::ROCK)
				{
					gameobject->DEATHFlag();
				}
			}
			player = new Player();
			player->BaseInitialize(input, audio, mouse, collision, gameObjectManager->GetGameObjects());
			player->Initialize();
			pHP = player->GetHP();
			gameObjectManager->AddGameObject(player);
			gameObjectManager->Update();
			sceneChangeFlag = true;
		}
		if (sceneChangeFlag == false)
		{
			sceneSize.x += 8;
			sceneSize.y += 4.5;
		}
		else
		{
			sceneSize.x -= 8;
			sceneSize.y -= 4.5;
			if (sceneSize.x < 0 && sceneSize.y < 0)
			{
				gameState = GameState::TITLE;
			}
		}
	}
	else
	{
		if (sceneSize.x >= 1280 && sceneSize.y >= 720)
		{
			sceneChangeFlag = true;
		}
		if (sceneChangeFlag == false)
		{
			sceneSize.x += 8;
			sceneSize.y += 4.5;
		}
		else
		{
			sceneSize.x -= 8;
			sceneSize.y -= 4.5;
			if (sceneSize.x < 0 && sceneSize.y < 0)
			{
				gameState = GameState::OPERATION;
			}
		}
	}
}

void GameScene::PlaySprite()
{
	clear->LoadTexture(10, L"Resources/GameClear.png");
	clear = Sprite::Create(10, { 0.0f,0.0f });

	over->LoadTexture(11, L"Resources/GameOver.png");
	over = Sprite::Create(11, { 0.0f,0.0f });

	HPback->LoadTexture(12, L"Resources/HPback.png");
	HPback = Sprite::Create(12, { 0,0 }, { 1.0f,1.0f,1.0f,1.0f });
	HPback->SetSize({ 270,35 });

	HPber->LoadTexture(13, L"Resources/HP.png");
	HPber = Sprite::Create(13, { 5,5 }, { 1.0f,1.0f,1.0f,1.0f });
	HPber->SetSize(hpsize);
	HPber->SetPosition({ 10,5 });
	spriteCount = true;
}

void GameScene::OperationChange()
{
	if (mouse->TriggerMouseRight())
	{
		gameState = GameState::SCENECHANGE;
		audio->SoundPlayWave("decisionSE.wav", false);
		sceneChangeFlag = false;
		sceneCount = 4;
	}

	if (mouse->TriggerMouseLeft())
	{
		operationCount = true;
	}
	if (operationCount == true)
	{
		operationPos.x -= 20;
		rulePos.x -= 20;
		if (operationPos.x <= -1280)
		{
			operationCount = false;
			gameState = GameState::RULE;
		}
	}
}

void GameScene::ruleChange()
{
	if (mouse->TriggerMouseLeft())
	{
		gameState = GameState::SCENECHANGE;
		audio->SoundPlayWave("decisionSE.wav", false);
		sceneChangeFlag = false;
		sceneCount = 1;
	}
	if (mouse->TriggerMouseRight())
	{
		operationCount = true;
	}
	if (operationCount == true)
	{
		operationPos.x += 20;
		rulePos.x += 20;
		if (rulePos.x >= 1280)
		{
			operationCount = false;
			gameState = GameState::OPERATION;
		}
	}
}
