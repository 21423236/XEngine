#ifndef __CAMERA__
#define __CAMERA__

#include "PreHeader.h"

//ÿ֡����Frame�ı�һ����ͼ����
class Camera
{
public:
    Camera();
    
    //��x��ת������PiΪ��λ
    void Pitch(float );

    //��y��ת������PiΪ��λ
    void Yaw(float );

    //��z��ת������PiΪ��λ
    void Roll(float );

    //��z,x,y�᷽���ƶ�
    void MoveRightBy(float );
    void MoveUpBy(float );
    void MoveForwardBy(float );

    //�仯��ͼ����
    void Frame();

    //�����۾���λ��
    void SetEye(XMVECTOR& );

    //�õ���ͼ����
    const XMMATRIX GetViewMatrix();

    //�õ��۾���λ��
    XMVECTOR GetEyePosition();
private:
    XMVECTOR    eye;    //�۾�����λ��
    XMVECTOR    up;     //���ϵ�����
    XMVECTOR    at;     //�۲�����λ��

    XMFLOAT4X4    move;   //ƽ�ƾ���
    XMFLOAT4X4    rotate; //��ת����
    XMFLOAT4X4    view;   //��ͼ����(w->v)
};

#endif