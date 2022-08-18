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


	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input,mouse);

	ObjectFBX::SetDevice(dxCommon->GetDev());
	ObjectFBX::SetCamera(camera);
	ObjectFBX::CreateGraphicsPipeline();

	//FBX�p
	camera->SetTarget({ 0,3,0 });
	camera->SetDistance(10.0f);


	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	//�f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	// �e�N�X�`���ǂݍ���
	sprite->LoadTexture(2, L"Resources/lockOn.png");

	sprite = Sprite::Create(2, { 100.0f,100.0f }, { 1.0f,1.0f,1.0f,1.0f }, { 0.5f,0.5f });

	sprite->SetSize(lockSize);

	//audio->SoundLoadWave("Alarm01.wav");//�e�X�g

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
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//object->Draw(cmdList);


	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCmdList());

	//3D�I�u�W�F�N�g�̕`��
	enemy->Draw();
	player->Draw();
	
	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	Sprite::PreDraw(cmdList);

	if (count == 0)
	{
		sprite->Draw();
	}
	// �f�o�b�O�e�L�X�g�̕`��
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
