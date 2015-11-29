#ifndef __XENGINE__
#define __XENGINE__

#include "PreHeader.h"


class Input;
class Timer;
class RenderSystem;
class SoundMgr;
class Sound;
class Scene;

class XEngine
{
private:
    Input           *input;         //�����豸�����̣���꣩
    Timer           *timer;         //��ʱ��    
    SoundMgr        *soundSystem;  //����ϵͳ
    Sound           *music;
    RenderSystem    *renderSystem;    //��Ⱦϵͳ
   
    //windowsӦ�ó���������
    HWND        hwnd;
    LPCWSTR     appName;
    HINSTANCE   hinstance;

    //��ǰ������Ⱦ�ĳ���
    Scene   *currentScene;
    
public:
    ~XEngine(){};

    static XEngine* GetInstance();

    //��ʼ������
    BOOL Init(HINSTANCE );

    //�ر�����
    void Shutdown();

    //�������棬������Ϣ����
    void Run();

    //����һ������
    void LoadScene(Scene* );

    //ж��һ������
    void DumpScene();

    //��ȡ��ǰ����
    Scene* GetCurrentScene();

    void SetInputHandler(Input* );

    //��Ϣ������
    bool CALLBACK MessageHandler(UINT , WPARAM , LPARAM );
    
    //��Ϣ������
    static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private:
    BOOL InitWnd(int , int );
    XEngine();
    XEngine(const XEngine& );
    XEngine& operator = (const XEngine& );
};

#endif 