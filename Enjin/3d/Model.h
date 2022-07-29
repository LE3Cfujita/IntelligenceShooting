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
//3Dモデル
class Model
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://静的メンバ関数
	//OBJファイルから3Dモデルを読み込む
	static Model* LoadFormOBJ(const std::string& modelname);


	/// <summary>
/// 描画
/// </summary>
///<param name="cmdList">描画コマンドリスト</param>
/// ///<param name="rootParamIndexMaterial">マテリアル用ルートパラメータ番号</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);

	/// <summary>
/// デスクリプタヒープの初期化
/// </summary>
/// <returns></returns>
	void InitializeDescriptorHeap();

private://メンバ関数

	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);


	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);

	void CreateBuffers();


private://非公開のメンバ関数
	//OBJファイルから3Dモデルを読み込む(非公開)
	void LoadFormOBJInternal(const std::string& modelname);


public: // サブクラス
// 頂点データ構造体
	struct VertexPosNormalUv
	{
		DirectX::XMFLOAT3 pos;//xyz座標
		DirectX::XMFLOAT3 normal; //法線ベクトル
		DirectX::XMFLOAT2 uv;	//uv座標
	};
	// マテリアル
	struct Material
	{
		std::string name;	// マテリアル名
		DirectX::XMFLOAT3 ambient;	// アンビエント影響度
		DirectX::XMFLOAT3 diffuse;	// ディフューズ影響度
		DirectX::XMFLOAT3 specular;	// スペキュラー影響度
		float alpha;		// アルファ
		std::string textureFilename;	// テクスチャファイル名
		// コンストラクタ
		Material() {
			ambient = { 0.3f, 0.3f, 0.3f };
			diffuse = { 0.0f, 0.0f, 0.0f };
			specular = { 0.0f, 0.0f, 0.0f };
			alpha = 1.0f;
		}
	};


	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		DirectX::XMFLOAT3 ambient; // アンビエント係数
		float pad1; // パディング
		DirectX::XMFLOAT3 diffuse; // ディフューズ係数
		float pad2; // パディング
		DirectX::XMFLOAT3 specular; // スペキュラー係数
		float alpha;	// アルファ
	};


private://静的メンバ変数
	//デバイス
	static ID3D12Device* device;


	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;

public://setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }


private://メンバ変数

	 // テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// 頂点バッファ
	 ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	 ComPtr<ID3D12Resource> indexBuff;
	// マテリアル
	 Material material;
	 // デスクリプタヒープ
	  ComPtr<ID3D12DescriptorHeap> descHeap;

	// 頂点バッファビュー
	 D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	 D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	//static VertexPosNormalUv vertices[vertexCount];
	 std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	//static unsigned short indices[planeCount * 3];
	 std::vector<unsigned short> indices;

	 // シェーダリソースビューのハンドル(CPU)
	 CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	 // シェーダリソースビューのハンドル(CPU)
	 CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;


	 Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ
};

