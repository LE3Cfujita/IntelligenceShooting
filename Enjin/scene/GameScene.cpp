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
	safe_delete(object3d_3);
	safe_delete(sprite);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio, Mouse* mouse)
{
	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	this->mouse = mouse;
	gameState = GameState::TITLE;

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input, mouse);

	//FBX用
	camera->SetTarget({ 0,3,0 });
	camera->SetDistance(10.0f);


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


	audio->SoundLoadWave("Alarm01.wav", 0);//テスト
	audio->SoundLoadWave("decisionSE.wav", 1);//テスト
	audio->SoundVolume(0, bgmVolume * volumeSize);
	audio->SoundVolume(1, seVolume * volumeSize);

	audio->SoundPlayWave("Alarm01.wav", true);


	enemy = new Enemy;
	player = new Player;
	key = new OptionKey;
	key->Initialize(input, mouse);
	enemy->Initialize(player);
	player->Initialize(input, mouse, key);
	left = key->GetLeftDecimal();
	right = key->GetRightDecimal();
	up = key->GetUpDecimaly();
	down = key->GetDownDecimal();
	attack = key->GetAttackDecimal();

	LoadFile();


}

void GameScene::Update(WinApp* winApp)
{
	winApp->GetHwnd();

	Setting(winApp);
	Text();

	BCollision();

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
		ShowCursor(FALSE);
		player->Update();
		enemy->Update();
		SceneChange();

		SetCursorPos(690, 360);
		break;
	case GameState::OVER://ゲームオーバー
		break;

	case GameState::CLEA://ゲームクリア
		break;
	}
	camera->Update();
	mouse->Update();
}

void GameScene::Title()
{

	if (mousePos.x >= 480 && mousePos.x <= 800)
	{
		if (mousePos.y >= 400.0f && mousePos.y <= 500.0f)
		{
			yajirusiPos.y = 465.0f;
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::PLAY;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		if (mousePos.y >= 550.0f && mousePos.y <= 650.0f)
		{
			yajirusiPos.y = 600.0f;
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::OPTION_SELECT;
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
	}
	yajirusi->SetPosition(yajirusiPos);
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
	int sensiNumber = player->GetSensi();//表示する数字

	if (player->GetSensi() == 100)
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
		enemy->Draw();
		player->Draw();
		break;
	case GameState::OVER://ゲームオーバー
		break;

	case GameState::CLEA://ゲームクリア
		break;

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
		break;
	case GameState::OVER://ゲームオーバー
		break;

	case GameState::CLEA://ゲームクリア
		break;

	}
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	Sprite::PostDraw();


}

void GameScene::Option_Sensi()
{



}

void GameScene::Text()
{
	pHP = player->GetHP();

	eHP = enemy->GetHP();

	sprintf_s(str, "mousePosX = %f", mousePos.x);
	debugText.Print(str, 0, 0, 1);
	sprintf_s(str2, "mousePosY = %f", mousePos.y);
	debugText.Print(str2, 0, 20, 1);
}

void GameScene::BCollision()
{
	XMFLOAT3 bPosition = enemy->GetBPosition();
	XMFLOAT3 pPosition = player->GetPosition();

	if (enemy->GetBFlag() == 1)
	{
		if (collision->ballToball(pPosition.x, pPosition.y, pPosition.z, bPosition.x, bPosition.y, bPosition.z, 0.5, 0.5))
		{
			player->Hit();
			enemy->BHit();
		}
	}


	for (int i = 0; i < EBULLET_MAX; i++)
	{
		barragePosition[i] = enemy->GetBarragePosition();

		if (enemy->GetBarrageFlag() == 1)
		{
			if (collision->ballToball(pPosition.x, pPosition.y, pPosition.z, barragePosition[i].x, barragePosition[i].y, barragePosition[i].z, 2, 2))
			{
				player->Hit();
				enemy->BarrageHit();
			}
		}
		enemy->PlusNumber();
	}
	//敵の座標
	XMFLOAT3 ePosition = enemy->GetPosition();
	//プレイヤー弾の座標
	for (int i = 0; i < PBULLET_MAX; i++)
	{
		pBPosition[i] = player->GetBPosition();
		if (enemy->GetHP() != 0)
		{
			if (collision->ballToball(ePosition.x, ePosition.y, ePosition.z, pBPosition[i].x, pBPosition[i].y, pBPosition[i].z, 10, 1))
			{
				player->PHit();
				enemy->PHit();
			}
		}
		player->PlusNumber();
	}

	if (enemy->GetRushCount() == 0)
	{
		if (collision->ballToball(pPosition.x, pPosition.y, pPosition.z, ePosition.x, ePosition.y, ePosition.z, 1, 3))
		{
			player->RushHit();
			enemy->RushHit();
		}
	}

}

void GameScene::SceneChange()
{
	if (pHP <= 0)
	{
		gameState == GameState::OVER;//ゲームオーバー
	}
	if (eHP <= 0)
	{
		gameState == GameState::CLEA;//ゲームクリア
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
			}
		}
		//ひだり
		if (pos.y >= 317 && pos.y <= 375)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(2);
				keyCount = 2;
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
			}
		}
		//みぎ
		if (pos.y >= 317 && pos.y <= 375)
		{
			if (mouse->TriggerMouseLeft())
			{
				key->SetCount(4);
				keyCount = 4;
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
		keyCount = key->GetCount();
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
	SaveData Data = { left,right,up,down,attack };
	FILE* fp;
	fopen_s(&fp, "text.txt", "w");
	fwrite(&Data, sizeof(Data), 1, fp);//ひだりキーの値の入力
	fclose(fp);
}

void GameScene::LoadFile()
{

	SaveData Data;
	FILE* fp;
	fopen_s(&fp, "text.txt", "r");
	if (fp != NULL)
	{
		fread(&Data, sizeof(Data), 1, fp);
		fclose(fp);
		left = Data.left;
		right = Data.right;
		up = Data.up;
		down = Data.down;
		attack = Data.attack;

		key->SetLeftDecimal(left);
		key->SetRightDecimal(right);
		key->SetUpDecimaly(up);
		key->SetDownDecimal(down);
		key->SetAttackDecimal(attack);
		player->GetKey();
	}
}
