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

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input, mouse);

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
	sprite->LoadTexture(2, L"Resources/title.png");

	sprite = Sprite::Create(2, { 0.0f,0.0f });

	// �e�N�X�`���ǂݍ���
	yajirusi->LoadTexture(3, L"Resources/yazirusi.png");

	yajirusi = Sprite::Create(3, yajirusiPos);

	// �e�N�X�`���ǂݍ���
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
	player->Initialize(input, mouse);


}

void GameScene::Update(WinApp* winApp)
{


	//Text();

	BCollision();

	switch (gameState)
	{
	case GameState::TITLE://�^�C�g��
		Title();
		break;
	case GameState::OPSTION://��������Ȃ�
		Option();
		break;
	case GameState::PLAY://�Q�[���V�[��
		ShowCursor(FALSE);
		object->Update();
		player->Update();
		enemy->Update();

		SetCursorPos(690, 360);
		break;
	case GameState::OVER://�Q�[���I�[�o�[
		break;

	case GameState::CLEA://�Q�[���N���A
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
	//�e���̒l�����o��
	char eachNumber[3] = {};//�e���̒l
	int number = bgmVolume;//�\�����鐔��

	int keta = 100;//�ŏ��̌�

	for (int i = 0; i < 3; i++)
	{
		eachNumber[i] = number / keta;//���̌��̒l�����߂�
		number = number % keta;//���̌��ȉ��̒l�����o��
		keta = keta / 10;//����i�߂�
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
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//object->Draw(cmdList);


	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCmdList());


	switch (gameState)
	{
	case GameState::TITLE://�^�C�g��
		break;

	case GameState::OPSTION://��������Ȃ�
		break;
	case GameState::PLAY://�Q�[���V�[��
	//3D�I�u�W�F�N�g�̕`��
		enemy->Draw();
		player->Draw();
		break;
	case GameState::OVER://�Q�[���I�[�o�[
		break;

	case GameState::CLEA://�Q�[���N���A
		break;

	}

	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	Sprite::PreDraw(cmdList);

	switch (gameState)
	{
	case GameState::TITLE://�^�C�g��
		sprite->Draw();
		yajirusi->Draw();
		break;
	case GameState::OPSTION://��������Ȃ�
		sprite->Draw();
		opsion->Draw();
		DrawPercent();
		break;
	case GameState::PLAY://�Q�[���V�[��
		break;
	case GameState::OVER://�Q�[���I�[�o�[
		break;

	case GameState::CLEA://�Q�[���N���A
		break;

	}
	// �f�o�b�O�e�L�X�g�̕`��
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
	//�G�̍��W
	XMFLOAT3 ePosition = enemy->GetPosition();
	//�v���C���[�e�̍��W
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
			gameState == GameState::OVER;//�Q�[���I�[�o�[
		}
		if (eHP <= 0)
		{
			gameState == GameState::CLEA;//�Q�[���N���A
		}
	}
}
