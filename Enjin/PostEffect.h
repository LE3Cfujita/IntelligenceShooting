#pragma once
#include "Sprite.h"
#include"Input.h"
class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PostEffect();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �`��R�}���h
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);
    /// <summary>
    /// �V�[���`��O����
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`��㏈��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGraphicsPipelineState();
    /// <summary>
   /// �p�C�v���C������
   /// </summary>
    void CreateGraphicsPipelineState2();

public://�Ò�������o�ϐ�
    //��ʃN���A�J���[
    static const float clearColor[4];

private://�����o�ϐ�
    ComPtr<ID3D12Resource>texBuff;
    //SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap>descHeapSRV;

    //�[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    //RTV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;

    //�O���t�B�b�N�X�p�C�v���C��
    ComPtr<ID3D12PipelineState>pipelineState;
    //���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature>rootSignature;
};

