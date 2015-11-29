#ifndef __OBJ__
#define __OBJ__

#include "RenderableThing.h"

class RenderSystem;

using VERTICE::PosNormalTexTan;

class Obj : public RenderableThing
{
protected:
    PosNormalTexTan *vertices;   //������Ⱦ�Ķ���          
    DWORD           *indices;    //����
    
    UINT32          vcount;
    UINT32          icount;

    Material        mate;       //����
    UINT32          vertCount;  //��������

public:
    Obj();
    virtual ~Obj();

    void CreateTestTriangle();

    void CreateBox(float width, float height, float depth, const Material &material = Material() );

    void CreateGrid(float width, float height, UINT32 m, UINT32 n, const Material &material = Material());

    void CreateSphere(float radius, int slice, int stack, const Material &material = Material());
    
    void AssembleShadowMapVertices();

    void SetMaterial(const Material &material);

    const Material& GetMaterial() const;

    UINT32 GetVerticeCount() const;

    virtual void Update(float time);

private:
    
    BOOL InitBuffers();
    
    void Release();
};

#endif