#ifndef __MODEL__
#define __MODEL__

#include "RenderableThing.h"

class RenderSystem;

using VERTICE::PosNormalTexTan;

class Model :public RenderableThing
{
public:
    typedef unordered_map<string, shared_ptr<Material>>     MateTable;
    struct SubMesh
    {
        string  mate;       //��������
        int     startIndex; //�Ӽ���Ӧ��������ʼ���
        int     indexCount; //�Ӽ���Ӧ��������Ŀ
    };
protected:
    vector<PosNormalTexTan> vertices;   //����
    vector<DWORD>    indices;    //����
    UINT32          vertCount;

    vector<XMFLOAT3>		poses;          //����ģ��ʱλ��
    vector<XMFLOAT3>		normals;        //����ģ��ʱ����
    vector<XMFLOAT2>		texturePoses;   //����ģ��ʱ��������

    string      filePath;   //ģ������·��
    vector<SubMesh> meshs;   //������Ϣ
    MateTable   mateTable;  //���ʱ�

public:
    Model();
    virtual ~Model();

    //����ģ���ļ�
    BOOL LoadModel(const string &path, const string &fileName);

    //�ͷ���Դ
    void Release();

    //��ȡ������Ϣ
    const vector<SubMesh>& GetMeshes() const;

    //��ȡ���ʱ�
    const MateTable& GetMateTable() const;

    virtual void Update(float time);

private:
    // ��ȡ������Ϣ��λ�á��������ߣ�
	BOOL ParseVertices(const string &fileName);

	// ���������ļ�
	BOOL ParseMaterialFile(const string &fileName);

	// ����������submesh���ṹ
	BOOL ParseSubset(const string &fileName);
	
    //��ʼ��������
    BOOL InitBuffers();

    //�����Ӱ��ͼ���㻺��
    void Model::AssembleShadowMapVertices();
};

#endif