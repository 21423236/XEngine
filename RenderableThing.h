#ifndef __RENDERABLE__
#define __RENDERABLE__

#include "PreHeader.h"
#include "Vertice.h"
#include "Light.h"
#include "Utility.h"
#include "Geometry.h"
#include "Input.h"

class RenderableThing
{
public:
    enum RenderType
    {
        PARTICLE = 0,
        OBJ = 1,
        MODEL,
        SKELETON
    };

    typedef shared_ptr<RenderableThing> RenVal;
protected:
    RenderType      type;
    ID3D11Buffer    *verticesBuffer;    //���㻺��
    ID3D11Buffer    *indicesBuffer;     //��������
    ID3D11Buffer    *shadowMapVerticesBuffer;   //��Ӱ��ͼ���㻺��
    XMFLOAT3        *shadowMapVertices; //��Ӱ��ͼ�Ķ���

    float           x, y, z;    //��������
    XMFLOAT4X4      world;  //�������
    XMFLOAT4X4      move;   //ƽ�ƾ���
    XMFLOAT4X4      rotate; //��ת����
    float           scale;  //��������

    XMFLOAT4X4      pworld;  //���ڵ��������
    XMFLOAT4X4      protate; //���ڵ���ת����
    float           pscale;  //���ڵ��������

    RenderableThing*parent;
    vector<RenVal>  children;

    BOOL            isHandleInput;
public:
    RenderableThing()
    {
        verticesBuffer = NULL;
        indicesBuffer = NULL;
        shadowMapVerticesBuffer = NULL;
        shadowMapVertices = NULL;
        parent = NULL;

        x = 1;
        y = 1;
        z = 1;
        XMStoreFloat4x4(&world, XMMatrixIdentity());
        XMStoreFloat4x4(&rotate, XMMatrixIdentity());

        XMStoreFloat4x4(&pworld, XMMatrixIdentity());
        XMStoreFloat4x4(&protate, XMMatrixIdentity());
        XMStoreFloat4x4(&move, XMMatrixIdentity());

        scale = 1.0f;
        pscale = 1.0f;
        isHandleInput = FALSE;
    }

    virtual ~RenderableThing()
    {
        SafeRelease(verticesBuffer);
        SafeRelease(indicesBuffer);
        SafeRelease(shadowMapVerticesBuffer);
        ReleasNewArray(shadowMapVertices);
        parent = NULL;
    }

    //����Ӷ���
    void AddChild(RenderableThing *child)
    {
        child->parent = this;
        children.push_back(RenVal(child));
    }

    //����Ӷ���
    void AddChild(RenVal child)
    {
        child->parent = this;
        children.push_back(child);
    }

    //��ȡ��������
    RenderType GetRenderType()
    {
        return type;
    }

    //���������е�λ��
    void SetPosition(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
        XMMATRIX temp = XMMATRIX(1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            x,y,z,1);
        XMStoreFloat4x4(&world, temp);
    }

    //��ȡ�������
    const XMMATRIX GetWorldMatrix() const
    {
        XMMATRIX temp = XMLoadFloat4x4(&move)*XMLoadFloat4x4(&rotate);
        temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&world));
        temp = XMLoadFloat4x4(&pworld) * temp;
        float   ts = pscale * scale;
        XMStoreFloat4x4(const_cast<XMFLOAT4X4*>(&move), XMMatrixIdentity());
        XMStoreFloat4x4(const_cast<XMFLOAT4X4*>(&rotate), XMMatrixIdentity());
        XMStoreFloat4x4(const_cast<XMFLOAT4X4*>(&world), temp);
        return XMMatrixScaling(ts, ts, ts) * temp;
    }

    //�����������
    Position GetWorldPosition()
    {
        return Position(x, z);
    }

    //��ȡ���㻺��
    ID3D11Buffer*const& GetVerticeBuffer() const
    {
        return verticesBuffer;
    }

    //��ȡ��������
    ID3D11Buffer*const& GetIndexBuffer() const
    {
        return indicesBuffer;
    }

    //��ȡ��Ӱ��ͼ���㻺��
    ID3D11Buffer*const& GetShadowMapVerticeBuffer() const
    {
        return shadowMapVerticesBuffer;
    }

    //��x��ת������PiΪ��λ
    void Pitch(float x)
    {
        XMMATRIX temp = XMMatrixMultiply(XMLoadFloat4x4(&rotate), XMMatrixRotationX(x));
        XMStoreFloat4x4(&rotate, temp);
    }

    //��y��ת������PiΪ��λ
    void Yaw(float y)
    {
        XMMATRIX temp = XMMatrixMultiply(XMLoadFloat4x4(&rotate), XMMatrixRotationY(y));
        XMStoreFloat4x4(&rotate, temp);
    }

    //��z��ת������PiΪ��λ
    void Roll(float z)
    {
        XMMATRIX temp = XMMatrixMultiply(XMLoadFloat4x4(&rotate), XMMatrixRotationZ(z));
        XMStoreFloat4x4(&rotate, temp);
    }

    //���÷�������
    void SetScale(float s)
    {
        scale = s;
    }

    //�����߼�
    virtual void Update(float time) = 0;

    //�����Լ�����ڸ��׵����������ת�������ű���
    void _UpdateByFather(float time)
    {
        for(auto it = children.begin(); it != children.end(); ++it)
        {
            XMStoreFloat4x4(&(*it)->pworld, GetWorldMatrix());
            (*it)->pscale = pscale * scale;
            (*it)->Update(time);
            (*it)->_UpdateByFather(time);
        }
    }

    //�õ��Լ����еĺ����б�
    vector<RenVal> GetChildren()
    {
        return children;
    }

    //��ӱ��۲������
    void AddObserveTarget(Input *input)
    {
        input->AddObserver(this);
    }

    void DeleteObserveTarget(Input *input)
    {
        input->DeleteObserver(this);
    }

    //�����Ƿ�������
    void SetHandleInput(BOOL flag)
    {
        isHandleInput = flag;
    }

    //����Ƿ�������
    BOOL IsHandleInput()
    {
        return isHandleInput;
    }

    //����������Ϣ
    virtual void HandleInput(Input *input)
    {
        
    }

protected:
    //�ͷź���
    virtual void Release() = 0;

    //��������
    virtual BOOL InitBuffers() = 0;

    //�����Ӱ��ͼ���㻺��
    virtual void AssembleShadowMapVertices() = 0;
};

#endif