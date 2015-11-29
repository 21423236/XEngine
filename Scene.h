#ifndef __SCENE__
#define __SCENE__

#include "PreHeader.h"
#include "SkyBox.h"
#include "Input.h"
#include "Light.h"
#include "Geometry.h"
#include "Terrain.h"
class Camera;
class QTree;

class Scene
{
public:
    Camera              *camera; //ͨ������������ͼ����
    XMFLOAT4X4          proj;   //ͶӰ����
protected:
    typedef uint64_t            Key;
    typedef shared_ptr<RenderableThing> Val;
    typedef unordered_map<Key, Val>     RenderTable;

    Input               input;
    RenderTable         renderTable;    //���������п���Ⱦ�����
    vector<Val>         visiableTable;  //�����пɼ�����
    shared_ptr<SkyBox>  skyBox;         //��պ�
    shared_ptr<Terrain> terrain;        //����
    shared_ptr<Light>   light;
    QTree               *qTree;     //�Ĳ��������ڿɼ��Բ���
public:
    Scene();
    virtual ~Scene();

    void Init(const Rect &);

    //���һ�������е�����
    void AddRenderableThing(RenderableThing& );
 
    //ɾ��һ�������е�����
    void DeleteRenderableThing(RenderableThing& );

    //�����պ���
    void AddSky(SkyBox* );

    //��ӵ���
    void AddTerrain(Terrain *);

    //���³����е�����
    virtual void Update(double time);

    //����������Ϣ
    virtual void HandleInput(Input *);

    //��ӵƹ�
    void AddLight(Light *);

    //��Ⱦ�����е�����
    void Draw();

    void Release();

private:
    //�ܷ񱻿���
    void VisibleTest();

    //չ������������ӽڵ�
    void UnfoldChildren(Val& );
};

#endif