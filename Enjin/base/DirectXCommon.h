#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
#pragma once
class DirectXCommon
{
private:

	//�f�o�C�X�̏�����
	Microsoft::WRL::ComPtr<ID3D12Device> dev;
	Microsoft::WRL::ComPtr<IDXGIFactory6> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeaps;

	// �o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap = nullptr;

	Microsoft::WRL::ComPtr<ID3D12Fence> fence;


public:
	//�f�o�C�X�擾
	//Microsoft::WRL::ComPtr<ID3D12Device>GetDev() { return dev; }

	ID3D12Device* GetDev() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
public://�����o�֐�
	//������
	void Initislize(WinApp*winApp);

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapchain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();
private:
	//WindowsAPI
	WinApp* winApp = nullptr;
	//�t�F���X�l
	UINT64 fenceVal = 0;
};



