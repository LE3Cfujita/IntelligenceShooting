#include "GameScene.h"

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

	camera->SetTarget({ 0,20,0 });
	camera->SetDistance(100.0f);


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

	
	model = FbxLoader::GetInstance()->LoadModelFromFile("cube");

	object = new ObjectFBX;
	object->Initialize();
	object->SetModel(model);
	object->SetPosition({ 0,15,15 });

	//OBJ���烂�f���f�[�^��ǂݍ���
	modelGround = Model::LoadFormOBJ("ground");

	//3D�I�u�W�F�N�g����
	ground = Object3d::Create();



	//�I�u�W�F�N�g�Ƀ��f����R�t����
	ground->SetModel(modelGround);
	//3D�I�u�W�F�N�g�̈ʒu���w��
	ground->SetPosition({ -5,0,-5 });
}

void GameScene::Update(WinApp* winApp)
{


	Text();



	camera->Update();
	ground->Update();
	object->Update();
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	object->Draw(cmdList);


	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCmdList());

	//3D�I�u�W�F�N�g�̕`��
	ground->Draw();
	
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
	sprintf_s(str, "sprite_posX = %d", mouse_pos.x);
	debugText.Print(str, 0, 0, 1);
	sprintf_s(str2, "sprite_posY = %d", mouse_pos.y);
	debugText.Print(str2, 0, 20, 1);



	sprintf_s(str3, "cursor_posX = %f", cursor_pos.x);
	debugText.Print(str3, 0, 40, 1);
	sprintf_s(str4, "cursor_posY = %f", cursor_pos.y);
	debugText.Print(str4, 0, 60, 1);
}

void GameScene::Delete()
{
	delete ground;
	delete object3d_2;
	delete object3d_3;
	//�X�v���C�g���
	delete sprite;
	//3D���f�����
	delete modelGround;
	delete model_2;

	delete model;
	delete object;

}
