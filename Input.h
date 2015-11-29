#ifndef __INPUT__
#define __INPUT__

#include"PreHeader.h"

class RenderableThing;

class Input
{
public:
    struct MouseState
    {
        POINTS  location;       //���λ��
        BOOL    leftButton;     //����Ƿ���
        BOOL    righBtutton;    //�Ҽ��Ƿ���
    };

    Input(){}

    virtual ~Input(){}

    BOOL Init(int , int );

    //����������Ϣ���������۲��߶���
    void CopyData(Input *);

    //��ѯ�����Ƿ���ĳ������
    BOOL IsPressed(unsigned int );
    
    //������״̬
    MouseState GetMouseState();
    
    //ÿ֡����һ�Σ����ڸ��¼��̺����״̬
    void Frame(UINT uMessage, WPARAM wParam, LPARAM lParam);

    //��ӹ۲���
    void AddObserver(RenderableThing *);

    //ɾ���۲���
    void DeleteObserver(RenderableThing *);

    //֪ͨ���й۲���
    void InforObservers();

private:
    static const unsigned int MAX_KEYS = 256;   //������󰴼�
    BOOL keyboard[MAX_KEYS];    //���̰�����¼
    MouseState  mouse;  //���״̬
    vector<RenderableThing*> observers;
};

#endif