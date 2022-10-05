#pragma once

#include <Windows.h>
#include <xaudio2.h>
#include <wrl.h>
#include <unordered_map>
#include <string>

/// <summary>
/// �I�[�f�B�I�R�[���o�b�N
/// </summary>
class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:
    // �{�C�X�����p�X�̊J�n��
    //STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};
    void OnVoiceProcessingPassStart(UINT32 BytesRequired) {};
    // �{�C�X�����p�X�̏I����
    STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};
    // �o�b�t�@�X�g���[���̍Đ����I��������
    STDMETHOD_(void, OnStreamEnd) (THIS) {};
    // �o�b�t�@�̎g�p�J�n��
    STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};
    // �o�b�t�@�̖����ɒB������
    STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext) {
        // �o�b�t�@���������
        delete[] pBufferContext;
    };
    // �Đ������[�v�ʒu�ɒB������
    STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};
    // �{�C�X�̎��s�G���[��
    STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};

};
class Audio
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public: // �T�u�N���X
    // �`�����N�w�b�_
    struct ChunkHeader
    {
        char id[4]; // �`�����N����ID
        int32_t size;  // �`�����N�T�C�Y
    };

    // RIFF�w�b�_�`�����N
    struct RiffHeader
    {
        ChunkHeader chunk;   // "RIFF"
        char type[4]; // "WAVE"
    };

    // FMT�`�����N
    struct FormatChunk
    {
        ChunkHeader chunk; // "fmt "
        WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
    };

    // �����f�[�^
    struct SoundData
    {
        // �g�`�t�H�[�}�b�g
        WAVEFORMATEX wfex;
        // �o�b�t�@�̐擪�A�h���X
        BYTE* pBuffer;

        // �o�b�t�@�̃T�C�Y
        unsigned int bufferSize;
    };

public: //�����o�֐�
    bool Initialize();

    /// <summary>
    /// �T�E���h�ǂݍ���(.wav)
    /// </summary>
    /// <param name="filename">�t�@�C����</param>
    void SoundLoadWave(const char* filename, float number);

    /// <summary>
    /// 
    /// </summary>
    void SoundUnload();

    /// <summary>
    /// �T�E���h�Đ�(.wav)
    /// </summary>
    /// <param name="filename">�t�@�C����</param>
    /// <param name="loopFlag">���[�v���邩�ۂ�</param>
    void SoundPlayWave(const char* filename, bool loopFlag);

    /// <summary>
    /// �T�E���h��~(.wav)
    /// </summary>
    /// <param name="filename">�t�@�C����</param>
    void SoundStop(const char* filename);

    void SoundVolume(int number,float volume);

private: // �����o�ϐ�
    ComPtr<IXAudio2>xAudio2;
    IXAudio2MasteringVoice* masterVoice;
    XAudio2VoiceCallback voiceCallback;
    std::unordered_map<std::string, SoundData> soundDatas;
    std::unordered_map<std::string, IXAudio2SourceVoice*> sourceVoices;

    const std::string baseDirectory = "Resources/Audio/";
};