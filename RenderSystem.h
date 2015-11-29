#ifndef __RENDER__
#define __RENDER__

#include "PreHeader.h"
#include "RenderableThing.h"
class Obj;
class Model;
class SkyBox;
class Skeleton;
class Particle;
class EffectMgr;
class Terrain;
class RenderTexture;
class TerrainShader;

struct Material;
struct Light;

class RenderSystem
{
private:
    typedef uint64_t                    Key;
    typedef shared_ptr<RenderableThing> Val;
    typedef unordered_map<Key, Val>     RenderTable;

private:
    //��Ҫ��d3d�豸
    ID3D11Device            *device;
    IDXGISwapChain          *swapChain;
	ID3D11DeviceContext     *deviceContext;
	ID3D11RenderTargetView  *renderTargetView;

    EffectMgr               *effectMgr;
    vector<string>          shadersName;

    ID3DX11Effect           *lightEffect;    //������ȾЧ��
    ID3DX11EffectTechnique  *directionLightTech;  //ƽ�й���Ⱦ��
    ID3DX11EffectTechnique  *pointLightTech;    //���Դ��Ⱦ��
    ID3DX11EffectTechnique  *spotLightTech; //�۹��Դ��Ⱦ��

    ID3DX11Effect           *shadowMapEffect;   //��Ӱ��ͼ��ȾЧ��
    ID3DX11EffectTechnique  *shadowMapTech; //��Ӱ��ͼ��Ⱦ��

    ID3DX11Effect           *testEffect;    //������ȾЧ��
    ID3DX11EffectTechnique  *testTech;      //������Ⱦ��

    ID3DX11Effect           *currentEffect; //��ǰʹ�õ���ȾЧ��
    ID3DX11EffectTechnique  *currentTech;   //��ǰʹ�õ���Ⱦ��
    ID3D11InputLayout       *currentLayout; //��ǰʹ�õĶ��㲼��

    ID3D11Texture2D         *depthStencilBuffer;
    ID3D11DepthStencilView  *depthStencilView;  //���ģ����ͼ
    ID3D11DepthStencilState *depthStencilState; //��Ȳ���״̬

    ID3D11Texture2D         *shadowMapBuffer;   //��Ӱ��ͼ����
    ID3D11DepthStencilView  *DS_SMView;  //���ģ��-��Ӱ��ͼ��ͼ
    ID3D11ShaderResourceView *shadowMapView;     //��Ӱ��ͼ��ͼ

    RenderTexture           *renderTexture;

    XMFLOAT4    eyePos;
    BOOL        shadowFlag;

    XMMATRIX    lightView;
    XMMATRIX    lightProj;

    Light                   _light;
    XMMATRIX                _view;
    XMMATRIX                _proj;
    TerrainShader           *terrainShader;

    int         width;   //���ڳ�ʼ����
    int         height;  //���ڳ�ʼ����
    UINT        msaaQuality;    //�����Ⱦ��������

    vector<const Obj*>   objs;
    vector<const Model*> models;
    vector<const Skeleton*> skeletons;
    vector<Particle*> particles;
public:
    ~RenderSystem(){};
    
    //����   
    static RenderSystem* GetInstance();
    
    BOOL Init(HWND hwnd);   

    void Shutdown();
    
    //������Ⱦ��������
    void DrawRenderables(const vector<Val>& );

    //���õ�ǰ��Effect��Tech��Layout
    void SetCurrentETL(ID3DX11Effect *, ID3DX11EffectTechnique *, ID3D11InputLayout *);

    //�Ƿ����ӰЧ��
    void SetShadowOpen(BOOL );

    //��Ⱦ���
    void DrawSky(const SkyBox * , XMMATRIX &);

    //��Ⱦ����
    void DrawTerrain(Terrain *);

    void SetMaterial(const Material* material);

    void SetDepthTest();

    void SetLight(const Light* );

    void SetProjection(const XMMATRIX& );

    void SetView(const XMMATRIX& );

    void SetEye(const XMVECTOR& );

    BOOL CreateBuffer(const D3D11_BUFFER_DESC &, const D3D11_SUBRESOURCE_DATA &, ID3D11Buffer* &);

    void ClearBackground();

    void ClearDepthBuffer(ID3D11DepthStencilView *);

    void Present();

    ID3D11Device* getDevice();

    ID3D11DeviceContext* GetDeviceContext();

private:
    //��ȡ�����ļ�
    BOOL ReadShadersEtc();

    //��ʼ��D3D�豸
    BOOL InitD3D(HWND hwnd);

    //��ʼ�����ģ�建��
    BOOL InitDepthStencilView(DXGI_FORMAT format);

    //��ʼ����Ӱ��ͼ��ͼ
    BOOL InitShadowMapView(DXGI_FORMAT format);

    void ShutdownD3D();
    void ShutdownShaders();
    void ShutdownDepthStencil();

    //��Ⱦ��Ӱ��ͼ
    void _DrawShadowMap();

    //������Ⱦ��Ʒ
    void _DrawRenderables();

    //��ʼ���ƹ���Ӿ������ͶӰ����
    void InitLightVP(const Light* light);

    //���õƹ���Ӿ������ͶӰ����
    void SetLightVP();

    //����������ز���
    void SetParticleArgv(Particle*);

    //�ײ���Ⱦ����Ч��
    void _DrawParticles();

    //�ײ���Ⱦһ������
    void _DrawObj(const Obj* );

    //�ײ���Ⱦһ��ģ��
    void _DrawModel(const Model* , bool );

    //�ײ���Ⱦһ������
    void _DrawSkeleton(const Skeleton*, bool );

    RenderSystem();
};

#endif