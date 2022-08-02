#include"ModelFBX.h"
#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <cassert>
#include <string>

class FbxLoader
{
private://エイリアス
	//std::を省略
	using string = std::string;
public://定数
	//モデル格納ルートパス
	static const string baseDirectory;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device">ID3D12デバイス</param>
	void Initialize(ID3D12Device* device);
	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();
	/// <summary>
	/// ファイルからFBXモデル読込
	/// </summary>
	/// <param name="modelName">モデル名</param>
	//void LoadModelFromFile(const string& modelName);
	ModelFBX* LoadModelFromFile(const string& modelName);

	/// <summary>
	/// 再帰的にノード攻勢を解析
	/// </summary>
	/// <param name="model">読込先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	/// <param name="parent">親ノード</param>
	void ParseNodeRecursive(ModelFBX* model, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="model">読込先モデルオブジェクト</param>
	/// <param name="fbxNode">解析対象のノード</param>
	void ParseMesh(ModelFBX* model, FbxNode* fbxNode);

	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxMatrix& src);


	//サブ関数
	/****************/
	//頂点座標読み取り
	void ParseMeshVertices(ModelFBX* model, FbxMesh* fbxMesh);
	//面情報読み取り
	void ParseMeshFaces(ModelFBX* model, FbxMesh* fbxMesh);
	//マテリアル読み取り
	void ParseMaterial(ModelFBX* model, FbxNode* fbxNode);
	//テクスチャ読み込み
	void LoadTexture(ModelFBX* model, const std::string& fullpash);

	//スキニング情報の読み取り
	void ParseSkin(ModelFBX* model, FbxMesh* fbxMesh);

	/****************/

	//ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);


private:
	//D3D12デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポータ
	FbxImporter* fbxImporter = nullptr;

	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	static const string defaultTextureFileName;
};