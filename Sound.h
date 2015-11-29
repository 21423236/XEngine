#ifndef __SOUND__
#define __SOUND__

#include "PreHeader.h"

struct WaveHeaderType
{
    char chunkId[4];
    unsigned long chunkSize;
    char format[4];
    char subChunkId[4];
    unsigned long subChunkSize;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned long sampleRate;
    unsigned long bytesPerSecond;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    char dataChunkId[4];
    unsigned long dataSize;
};

class SoundMgr
{
public:
    //����
    static SoundMgr* GetInstance();

    ~SoundMgr();

    //��ʼ��DirectSound�豸��primaryBuffer
    BOOL Init(HWND);

    //�����豸
    void Shutdown();

    //��������豸���ͷ�DirectSound�豸��primaryBuffer
    IDirectSound8 * GetDevice();

private:

    SoundMgr();

    SoundMgr(const SoundMgr&){};

private:
    IDirectSound8* device;
    IDirectSoundBuffer* primaryBuffer;
};

class Sound
{
private:
    string fileName;
    DWORD playPos;
    IDirectSoundBuffer8* soundData;

public:
    Sound();
    ~Sound();
    
    //���������ļ�
    BOOL LoadFile(const string);

    //������Ƶ�ļ�
    void Play();

    //��ͣ
    void Pause();

    //ֹͣ
    void Stop();

    //�Ƿ����ڲ���
    BOOL IsPlaying();

    //�ͷ�soundData
    void Release();
};

class SoundBatch
{
private:
    map<string, IDirectSoundBuffer8*>   name2SoundTable;
public:
    ~SoundBatch();

    //����
    static SoundBatch* GetInstance();

    //����wav��ʽ��Ƶ�ļ�
    IDirectSoundBuffer8* LoadSound(const string &);

    //����ȡ��wav��ʽ��Ƶ�ļ�
    IDirectSoundBuffer8* GetSoundByName(const string &);

    //���
    void Clear();

private:
    SoundBatch(){};

    SoundBatch(const SoundBatch &){};

    SoundBatch & operator = (const SoundBatch &){};

    //�ж�������ļ���ʽ�Ƿ�Ϸ�
    BOOL IsLegal(const WaveHeaderType &);
};

#endif