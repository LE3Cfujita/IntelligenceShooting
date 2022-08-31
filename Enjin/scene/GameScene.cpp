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
	sprite->LoadTexture(2, L"Resources/lockOn.png");

	sprite = Sprite::Create(2, { 100.0f,100.0f }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	sprite->SetSize(lockSize);

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
	ShowCursor(FALSE);

}

void GameScene::Update(WinApp* winApp)
{


	Text();

	BCollision();

	switch (scene)
	{
	case 0://タイトル
		break;

	case 1://操作説明など
		break;
	case 2://ゲームシーン
		object->Update();
		player->Update();
		enemy->Update();
		break;
	case 3://ゲームオーバー
		break;

	case 4://ゲームクリア
		break;

	}
	SceneChange();
	camera->Update();
	mouse->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//object->Draw(cmdList);


	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());


	switch (scene)
	{
	case 0://タイトル
		break;

	case 1://操作説明など
		break;
	case 2://ゲームシーン
	//3Dオブジェクトの描画
		enemy->Draw();
		player->Draw();
		break;
	case 3://ゲームオーバー
		break;

	case 4://ゲームクリア
		break;

	}

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	Sprite::PreDraw(cmdList);

	if (count == 0)
	{
		sprite->Draw();
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
	if (scene == 2)
	{
		if (pHP <= 0)
		{
			scene = 3;//ゲームオーバー
		}
		if (eHP <= 0)
		{
			scene = 4;//ゲームクリア
		}
	}
}
