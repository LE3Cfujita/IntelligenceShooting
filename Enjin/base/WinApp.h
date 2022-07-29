#include<windows.h>
#pragma once
class WinApp
{public://�ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public://�����o�֐�
	//������
	void Initialize();
	//�X�V
	void Update();
	//�I��
	void Finalize();
	//���b�Z�[�W�̏���
	bool ProcessMessage();

private:
	//�E�B���h�E�n���h��
	HWND hwnd = nullptr; 

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
public:

	//getter
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHInstance() { return w.hInstance; }

	//�ÓI�����o�ϐ�

//�E�B���h�E�T�C�Y
	static const int window_width = 1280;  //����
	static const int window_height = 720;  //�c��
};

