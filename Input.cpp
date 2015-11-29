#include "Input.h"
#include "RenderableThing.h"

BOOL Input::Init(int w, int h)
{
    mouse.leftButton = FALSE;
    mouse.righBtutton = FALSE;
    mouse.location.x = w / 2;
    mouse.location.y = h / 2;
    ZeroMemory(keyboard, sizeof(keyboard));
    
    return TRUE;
}

void Input::CopyData(Input *input)
{
    input->mouse = mouse;
    memcpy(&input->keyboard, keyboard, sizeof(keyboard));
}

BOOL Input::IsPressed(unsigned int key)	
{ 
    return (key < MAX_KEYS) ? (keyboard[key] == TRUE) : FALSE; 
}

Input::MouseState Input::GetMouseState()
{
    return mouse;
}

void Input::Frame(UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch (uMessage)
    {
    case WM_KEYDOWN:    //���̰���
        if ((unsigned int)wParam < MAX_KEYS)
        {
            keyboard[(unsigned int)wParam] = TRUE; 
        }
        break;

    case WM_KEYUP:      //���̵���
        if ((unsigned int)wParam < MAX_KEYS)
        {
            keyboard[(unsigned int)wParam] = FALSE; 
        }
        break;

    case WM_LBUTTONDBLCLK:  //����������
        mouse.leftButton = TRUE;
        break;

    case WM_LBUTTONUP:      //����������
        mouse.leftButton = FALSE;
        break;

    case WM_RBUTTONDBLCLK:  //����Ҽ�����
        mouse.righBtutton = TRUE;
        break;

    case WM_RBUTTONUP:      //����Ҽ�����
        mouse.righBtutton = FALSE;
        break;

    case WM_MOUSEMOVE:      //����ƶ�������������û�����ԭ�����Ͻ�
        mouse.location = MAKEPOINTS(lParam);
        break;
    }
}

void Input::AddObserver(RenderableThing *obs)
{
    observers.push_back(obs);
}

void Input::DeleteObserver(RenderableThing *obs)
{
    for(auto it = observers.begin(); it != observers.end(); ++it)
    {
        if((*it) == obs)
        {
            observers.erase(it);
            break;
        }
    }
}

void Input::InforObservers()
{
    for(auto it = observers.begin(); it != observers.end(); ++it)
    {
        (*it)->HandleInput(this);
    }
}