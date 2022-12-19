#pragma once
#include "Sprite.h"
#include"Input.h"
class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 描画コマンド
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);
    /// <summary>
    /// シーン描画前処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// シーン描画後処理
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// パイプライン生成
    /// </summary>
    void CreateGraphicsPipelineState();
    /// <summary>
   /// パイプライン生成
   /// </summary>
    void CreateGraphicsPipelineState2();

public://静定期メンバ変数
    //画面クリアカラー
    static const float clearColor[4];

private://メンバ変数
    ComPtr<ID3D12Resource>texBuff;
    //SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap>descHeapSRV;

    //深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    //RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;

    //グラフィックスパイプライン
    ComPtr<ID3D12PipelineState>pipelineState;
    //ルートシグネチャ
    ComPtr<ID3D12RootSignature>rootSignature;
};

