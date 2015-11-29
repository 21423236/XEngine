#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "PreHeader.h"
#include "RenderableThing.h"

class Particle : public RenderableThing
{
private:
    ID3D11Buffer* drawVB;   //��Ⱦ����
	ID3D11Buffer* streamOutVB;  //�����Ŀ�껺��
    ID3D11ShaderResourceView *texRV;    //��������
    ID3D11ShaderResourceView* randomTexRV;  //�������

public:
	float timeStep; //ÿ���ε���֮���ʱ��
	float age;      //���ʱ��

    bool m_bFirstRun;
	UINT m_nMaxParticles;

	XMFLOAT4 emitDirW;  //���䷽��

public:
    Particle(); 

    ~Particle();

    BOOL Init(const string &filePath, const string &file);

    virtual void Update(float time);

    XMFLOAT4 GetWorldVertex();

    ID3D11Buffer*& GetDrawVertexBuffer()
    {
        return drawVB;
    }

    ID3D11Buffer* & GetStreamOutVertexBuffer()
    {
        return streamOutVB;
    }

    //���÷��䷽��
    void SetEmitDirect(XMFLOAT4 &);

    ID3D11ShaderResourceView* GetParticleSRV()
    {
        return texRV;
    }

    ID3D11ShaderResourceView* GetRandomSRV()
    {
        return randomTexRV;
    }

protected:
    virtual void Release();

    virtual BOOL InitBuffers();

    virtual void AssembleShadowMapVertices();

};

#endif