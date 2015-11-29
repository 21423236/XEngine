#ifndef __SKELETON__
#define __SKELETON__

#include "PreHeader.h"
#include "RenderableThing.h"
#include "Vertice.h"
#include "Utility.h"

using VERTICE::PosNormalTexTan;

struct VertexInfo
{
    int StartWeight;
	int WeightCount;
};

struct Joint
{
	string name;
	int parentID;

	XMFLOAT3 pos;
	XMFLOAT4 orientation;
};

struct Weight
{
	int jointID;
	float bias;
	XMFLOAT3 pos;
    XMFLOAT3 normal;
};

struct BoundingBox
{
	XMFLOAT3 min;
	XMFLOAT3 max;
};

struct FrameData
{
	int frameID;
	vector<float> frameData;
};

struct AnimJointInfo
{
	string name;
	int parentID;

	int flags;
	int startIndex;
};

struct ModelAnimation
{
	int numFrames;
	int numJoints;
	int frameRate;
	int numAnimatedComponents;

	float frameTime;
	float totalAnimTime;
	float currAnimTime;

	vector<AnimJointInfo> jointInfo;
	vector<BoundingBox> frameBounds;
	vector<Joint>	baseFrameJoints;
	vector<FrameData>	frameData;
	vector<vector<Joint>> frameSkeleton;
};


class Skeleton : public RenderableThing
{
public:
    struct SubMesh
    {
        vector<PosNormalTexTan> vertices;
        vector<VertexInfo>      vertInfos;
        vector<DWORD>           indices;
        vector<Weight>          weights;
        vector<XMFLOAT3>        positions;
        ID3D11ShaderResourceView    *texture;

        ID3D11Buffer    *verticesBuffer;    //���㻺��
        ID3D11Buffer    *indicesBuffer;     //��������
        ID3D11Buffer    *shadowMapVerticesBuffer;   //��Ӱ��ͼ���㻺��

        SubMesh()
        {
            texture = NULL;
            verticesBuffer = NULL;
            indicesBuffer = NULL;
            shadowMapVerticesBuffer = NULL;
        }

        ~SubMesh()
        {
            texture = NULL;
            verticesBuffer = NULL;
            indicesBuffer = NULL;
            shadowMapVerticesBuffer = NULL;
        }
    };

private:
    vector<Joint>   joints;     //�ؽ�����
    vector<SubMesh> meshs;      //������Ϣ
    vector<ModelAnimation> animations;  //��������

public:
    Skeleton()
    {
        type = SKELETON;
    };
    virtual ~Skeleton();

    //����ģ���ļ�
    BOOL LoadSkeleton(const string &path, const string &fileName);

    //���붯���ļ�
    BOOL LoadAnimation(const string &path, const string &fileName);

    //�ͷ���Դ
    void Release();

    //��ȡ������Ϣ
    const vector<SubMesh>& GetMeshes() const;

    void PlayAnimation(float time, int animation);

    virtual void Update(float time);

private:

    void InQuots(ifstream& , string& );

    void ParserJoints(ifstream&, int);

    void ParserMesh(ifstream& , const string & );

    void BuildPosition(SubMesh & );

    void BuildNormal(SubMesh & , int );
    
    BOOL ParserHierarchy(ifstream& , ModelAnimation& );

    void ParserBoundingBox(ifstream& , ModelAnimation& );

    void ParserBaseFrame(ifstream& , ModelAnimation& );

    void LoadAndBuildFrames(ifstream& , ModelAnimation& );

    //��ʼ��������
    BOOL InitBuffers();

    void AssembleShadowMapVertices();

};

#endif