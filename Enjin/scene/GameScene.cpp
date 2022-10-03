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
	safe_delete(model);
	safe_delete(object);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio, Mouse* mouse)
{
	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	this->mouse = mouse;

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input, mouse);

	ObjectFBX::SetDevice(dxCommon->GetDev());
	ObjectFBX::SetCamera(camera);
	ObjectFBX::CreateGraphicsPipeline();

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

	yajirusi = Sprite::Create(3, yajirusiPos);

	// テクスチャ読み込み
	opsion->LoadTexture(4, L"Resources/BGMSEOpsion.png");

	opsion = Sprite::Create(4, optionPos, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	
	opsion->SetSize({ 720,360 });

	if (!Sprite::LoadTexture(5, L"Resources/number.png")) {
		assert(0);
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		spriteNumber[i] = Sprite::Create(5, { (float)(i * 26 + 300),370 });
	}
	//audio->SoundLoadWave("Alarm01.wav");//テスト

	//audio->SoundPlayWave("Alarm01.wav", true);


	model = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	object = new ObjectFBX;
	object->Initialize();
	object->SetModel(model);
	object->PlayAnimation();
	//object->SetPosition({ 0,15,15 });


	enemy = new Enemy;
	player = new Player;
	enemy->Initialize(player);
	player->Initialize(input, mouse);


}

void GameScene::Update(WinApp* winApp)
{


	//Text();

	BCollision();

	switch (gameState)
	{
	case GameState::TITLE://タイトル
		Title();
		break;
	case GameState::OPSTION://操作説明など
		Option();
		break;
	case GameState::PLAY://ゲームシーン
		ShowCursor(FALSE);
		object->Update();
		player->Update();
		enemy->Update();

		SetCursorPos(690, 360);
		break;
	case GameState::OVER://ゲームオーバー
		break;

	case GameState::CLEA://ゲームクリア
		break;
	}
	SceneChange();
	camera->Update();
	mouse->Update();
}

void GameScene::Title()
{
	if (input->TriggerKey(DIK_RETURN))
	{
		if (count == 0)
		{
			gameState = GameState::PLAY;
		}
		else
		{
			gameState = GameState::OPSTION;
		}
	}
	if (input->TriggerKey(DIK_UP))
	{
		count = 0;
		yajirusiPos.y = 465.0f;
	}
	if (input->TriggerKey(DIK_DOWN))
	{
		count = 1;
		yajirusiPos.y = 600.0f;
	}
	yajirusi->SetPosition(yajirusiPos);
}

void GameScene::Option()
{

	if (input->TriggerKey(DIK_RETURN))
	{
		gameState = GameState::TITLE;
	}
}

void GameScene::DrawPercent()
{
	//各桁の値を取り出す
	char eachNumber[3] = {};//各桁の値
	int number = bgmVolume;//表示する数字

	int keta = 100;//最初の桁

	for (int i = 0; i < 3; i++)
	{
		eachNumber[i] = number / keta;//今の桁の値を求める
		number = number % keta;//次の桁以下の値を取り出す
		keta = keta / 10;//桁を進める
	}

	for (int i = 0; i < 3; i++)
	{
		spriteNumber[i]->SetSize({ 64,64 });
		spriteNumber[i]->SetTextureRect({ (float) ( 32 * eachNumber[i] ), 0, }, { 32,32 });
		spriteNumber[i]->SetPosition(XMFLOAT2{ numberPos.x + i * 60.0f, numberPos.y });
		spriteNumber[i]->Draw();
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//object->Draw(cmdList);


	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());


	switch (gameState)
	{
	case GameState::TITLE://タイトル
		break;

	case GameState::OPSTION://操作説明など
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
	case GameState::OPSTION://操作説明など
		sprite->Draw();
		opsion->Draw();
		DrawPercent();
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

void GameScene::Text()
{
	pHP = player->GetHP();

	eHP = enemy->GetHP();

	sprintf_s(str, "HP = %d", pHP);
	debugText.Print(str, 0, 0, 1);
	sprintf_s(str2, "sprite_posY = %d", mouse_pos.y);
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
			if (pBPosition[i].z >= 100)
			{
				int a = 0;
			}
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
	if (gameState == GameState::PLAY)
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
}
