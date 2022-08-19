#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma once
class Mouse
{
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �ÓI�����o�ϐ�
	static Mouse* GetInstance();

public: // �����o�֐�
/// <summary>
/// ������
/// </summary>
/// <returns>����</returns>
	bool Initialize(HINSTANCE hInstance, HWND hwnd);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
/// �L�[�̍��{�^���������`�F�b�N
/// </summary>
/// <returns>������Ă��邩</returns>
	bool PushMouseLeft();

	/// <summary>
	/// �L�[�̒��{�^���������`�F�b�N
	/// </summary>
	/// <returns>������Ă��邩</returns>
	bool PushMouseMiddle();

	/// <summary>
	/// �L�[�̍��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseLeft();

	/// <summary>
	/// �L�[�̒��{�^���g���K�[���`�F�b�N
	/// </summary>
	/// <returns>�g���K�[��</returns>
	bool TriggerMouseMiddle();

	/// <summary>
	/// �}�E�X�ړ��ʂ��擾
	/// </summary>
	/// <returns>�}�E�X�ړ���</returns>
	MouseMove GetMouseMove();

	float GetMouseVelocityX();
	float GetMouseVelocityY();

private://�����o�ϐ�
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};

};

