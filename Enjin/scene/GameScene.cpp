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

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio,Mouse* mouse)
{
	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;


	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input,mouse);

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
	player->Initialize(input);


}

void GameScene::Update(WinApp* winApp)
{


	Text();



	camera->Update();
	object->Update();
	player->Update();
	enemy->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//object->Draw(cmdList);


	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCmdList());

	//3Dオブジェクトの描画
	enemy->Draw();
	player->Draw();
	
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

	XMFLOAT3 p = player->GetPosition();

	XMFLOAT3 flag = enemy->GetPosition();

	sprintf_s(str, "flag = %f", flag.z);
	debugText.Print(str, 0, 0, 1);
	sprintf_s(str2, "sprite_posY = %d", mouse_pos.y);
	debugText.Print(str2, 0, 20, 1);

}

void GameScene::Delete()
{
	

}
