#ifndef __LIGHT__
#define __LIGHT__

#include"PreHeader.h"

//����
struct Light
{
    int         type;       //��������
    XMFLOAT4    position;   //��Դλ��
    XMFLOAT4    direction;  //���շ���

    XMFLOAT4    ambient;    //������ǿ��
    XMFLOAT4    diffuse;    //�������ǿ��
    XMFLOAT4    specular;   //�����ǿ��

    float       attenuation0;   //����˥������
    float       attenuation1;   //һ��˥������
    float       attenuation2;   //����˥������

    float       alpha;      //�۹���׶�Ƕ�
    float       beta;       //�۹���׶�Ƕ�
    float       falloff;    //�۹�˥��ϵ����һ��Ϊ1.0f
};

struct Material
{
    XMFLOAT4    ambient;    //�����ⷴ����
    XMFLOAT4    diffuse;    //������ⷴ����
    XMFLOAT4    specular;   //���淴��ⷴ����
    float       power;      //���淴��ϵ��
    ID3D11ShaderResourceView    *texture;   //������ͼ

    Material()
    {
        ambient.x = ambient.y = ambient.z = ambient.w = 0.5;
        diffuse.x = diffuse.y = diffuse.z = diffuse.w = 0.5;
        specular.x = specular.y = specular.z = specular.w = 0.5;
        power = 0.5;
        texture = NULL;
    }

    ~Material()
    {
        texture = NULL;
    }
};

#endif