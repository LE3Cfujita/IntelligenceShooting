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
		spriteBGMNumber[i] = Sprite::Create(5, { (float)(i * 26 + 300),370 });
		spriteSENumber[i] = Sprite::Create(5, { (float)(i * 26 + 300),370 });
	}


	audio->SoundLoadWave("Alarm01.wav", 0);//�e�X�g
	audio->SoundLoadWave("decisionSE.wav", 1);//�e�X�g
	audio->SoundVolume(0, bgmVolume * volumeSize);
	audio->SoundVolume(1, seVolume * volumeSize);

	audio->SoundPlayWave("Alarm01.wav", true);


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
	winApp->GetHwnd();

	//Text();

	BCollision();

	switch (gameState)
	{
	case GameState::TITLE://�^�C�g��
		Title();
		break;
	case GameState::OPSTION://��������Ȃ�
		Option(winApp);
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
			audio->SoundPlayWave("decisionSE.wav", false);
		}
		else
		{
			gameState = GameState::OPSTION;
			audio->SoundPlayWave("decisionSE.wav", false);
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

void GameScene::Option(WinApp* winApp)
{
	Setting(winApp);
	if (input->TriggerKey(DIK_RETURN))
	{
		gameState = GameState::TITLE;
	}
}

void GameScene::DrawPercent()
{
	//BGM
	/*************************/
	//�e���̒l�����o��
	char eachBGMNumber[3] = {};//�e���̒l
	int bgmNumber = bgmVolume;//�\�����鐔��

	if (bgmVolume == 100)
	{
		int keta = 100;//�ŏ��̌�
		for (int i = 0; i < 3; i++)
		{
			eachBGMNumber[i] = bgmNumber / keta;//���̌��̒l�����߂�
			bgmNumber = bgmNumber % keta;//���̌��ȉ��̒l�����o��
			keta = keta / 10;//����i�߂�
		}

		for (int i = 0; i < 3; i++)
		{
			spriteBGMNumber[i]->SetSize({ 64,64 });
			spriteBGMNumber[i]->SetTextureRect({ (float)(32 * eachBGMNumber[i]), 0, }, { 32,32 });
			spriteBGMNumber[i]->SetPosition(XMFLOAT2{ bgmNumberPos.x + i * 60.0f, bgmNumberPos.y });
			spriteBGMNumber[i]->Draw();
		}
	}
	else
	{
		int keta = 10;
		for (int i = 0; i < 2; i++)
		{
			eachBGMNumber[i] = bgmNumber / keta;//���̌��̒l�����߂�
			bgmNumber = bgmNumber % keta;//���̌��ȉ��̒l�����o��
			keta = keta / 10;//����i�߂�
		}

		for (int i = 0; i < 2; i++)
		{
			spriteBGMNumber[i]->SetSize({ 64,64 });
			spriteBGMNumber[i]->SetTextureRect({ (float)(32 * eachBGMNumber[i]), 0, }, { 32,32 });
			spriteBGMNumber[i]->SetPosition(XMFLOAT2{ bgmNumberPos.x + 60+ i * 60.0f, bgmNumberPos.y });
			spriteBGMNumber[i]->Draw();
		}
	}
	/**************************/
	//SE
	/**************************/
	//�e���̒l�����o��
	char eachSENumber[3] = {};//�e���̒l
	int seNumber = seVolume;//�\�����鐔��

	if (seVolume == 100)
	{
		int keta = 100;//�ŏ��̌�
		for (int i = 0; i < 3; i++)
		{
			eachSENumber[i] = seNumber / keta;//���̌��̒l�����߂�
			seNumber = seNumber % keta;//���̌��ȉ��̒l�����o��
			keta = keta / 10;//����i�߂�
		}

		for (int i = 0; i < 3; i++)
		{
			spriteSENumber[i]->SetSize({ 64,64 });
			spriteSENumber[i]->SetTextureRect({ (float)(32 * eachSENumber[i]), 0, }, { 32,32 });
			spriteSENumber[i]->SetPosition(XMFLOAT2{ seNumberPos.x + i * 60.0f, seNumberPos.y });
			spriteSENumber[i]->Draw();
		}
	}
	else
	{
		int keta = 10;
		for (int i = 0; i < 2; i++)
		{
			eachSENumber[i] = seNumber / keta;//���̌��̒l�����߂�
			seNumber = seNumber % keta;//���̌��ȉ��̒l�����o��
			keta = keta / 10;//����i�߂�
		}

		for (int i = 0; i < 2; i++)
		{
			spriteSENumber[i]->SetSize({ 64,64 });
			spriteSENumber[i]->SetTextureRect({ (float)(32 * eachSENumber[i]), 0, }, { 32,32 });
			spriteSENumber[i]->SetPosition(XMFLOAT2{ seNumberPos.x + 60 + i * 60.0f, seNumberPos.y });
			spriteSENumber[i]->Draw();
		}
	}
	/***************************/
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

void GameScene::Setting(WinApp* winApp)
{
	// �}�E�X���W���擾����
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(winApp->GetHwnd(), &p);

	XMFLOAT2 mousePos = { (float)p.x,(float)p.y };
	OptionCollision(mousePos);
	sprintf_s(str, "sprite_posX = %f", mousePos.x);
	debugText.Print(str, 0, 0, 1);
	sprintf_s(str2, "sprite_posY = %f", mousePos.y);
	debugText.Print(str2, 0, 20, 1);
}

void GameScene::OptionCollision(XMFLOAT2 pos)
{
	if (pos.x >= 450 && pos.x <= 950)
	{
		if (pos.y >= 245 && pos.y <= 320)
		{
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
		if (pos.y >= 330 && pos.y <= 402)
		{
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
		if (pos.y >= 420 && pos.y <= 495)
		{
			if (mouse->TriggerMouseLeft())
			{
				gameState = GameState::TITLE;
				audio->SoundStop("decisionSE.wav");
				audio->SoundPlayWave("decisionSE.wav", false);
			}
		}
		if (mouse->TriggerMouseRight())
		{
			gameState = GameState::TITLE;
			audio->SoundStop("decisionSE.wav");
			audio->SoundPlayWave("decisionSE.wav", false);
		}
	}
	audio->SoundVolume(0, bgmVolume * volumeSize);
	audio->SoundVolume(1, seVolume * volumeSize);
}
