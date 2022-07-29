#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <vector>
#include<Windows.h>
#include <cassert>
#include <d3dx12.h>
#include <string>
#include <DirectXTex.h>
using namespace std;
using namespace DirectX;
//3D���f��
class Model
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�ÓI�����o�֐�
	//OBJ�t�@�C������3D���f����ǂݍ���
	static Model* LoadFormOBJ(const std::string& modelname);


	/// <summary>
/// �`��
/// </summary>
///<param name="cmdList">�`��R�}���h���X�g</param>
/// ///<param name="rootParamIndexMaterial">�}�e���A���p���[�g�p�����[�^�ԍ�</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);

	/// <summary>
/// �f�X�N���v�^�q�[�v�̏�����
/// </summary>
/// <returns></returns>
	void InitializeDescriptorHeap();

private://�����o�֐�

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);


	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

	void CreateBuffers();


private://����J�̃����o�֐�
	//OBJ�t�@�C������3D���f����ǂݍ���(����J)
	void LoadFormOBJInternal(const std::string& modelname);


public: // �T�u�N���X
// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos;//xyz���W
		DirectX::XMFLOAT3 normal; //�@���x�N�g��
		DirectX::XMFLOAT2 uv;	//uv���W
	};
	// �}�e���A��
	struct Material
	{
		std::string name;	// �}�e���A����
		DirectX::XMFLOAT3 ambient;	// �A���r�G���g�e���x
		DirectX::XMFLOAT3 diffuse;	// �f�B�t���[�Y�e���x
		DirectX::XMFLOAT3 specular;	// �X�y�L�����[�e���x
		float alpha;		// �A���t�@
		std::string textureFilename;	// �e�N�X�`���t�@�C����
		// �R���X�g���N�^
		Material() {
			ambient = { 0.3f, 0.3f, 0.3f };
			diffuse = { 0.0f, 0.0f, 0.0f };
			specular = { 0.0f, 0.0f, 0.0f };
			alpha = 1.0f;
		}
	};


	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		DirectX::XMFLOAT3 ambient; // �A���r�G���g�W��
		float pad1; // �p�f�B���O
		DirectX::XMFLOAT3 diffuse; // �f�B�t���[�Y�W��
		float pad2; // �p�f�B���O
		DirectX::XMFLOAT3 specular; // �X�y�L�����[�W��
		float alpha;	// �A���t�@
	};


private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;


	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;

public://setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }


private://�����o�ϐ�

	 // �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// ���_�o�b�t�@
	 ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	 ComPtr<ID3D12Resource> indexBuff;
	// �}�e���A��
	 Material material;
	 // �f�X�N���v�^�q�[�v
	  ComPtr<ID3D12DescriptorHeap> descHeap;

	// ���_�o�b�t�@�r���[
	 D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	 D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	//static VertexPosNormalUv vertices[vertexCount];
	 std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	//static unsigned short indices[planeCount * 3];
	 std::vector<unsigned short> indices;

	 // �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	 CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	 // �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	 CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;


	 Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@
};

