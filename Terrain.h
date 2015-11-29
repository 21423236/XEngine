#ifndef __TERRAIN__
#define __TERRAIN__

#include "PreHeader.h"
#include "Obj.h"
#include <d3dx10math.h>
using VERTICE::PosNormalTex;

class Texture;

class Terrain
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR3 normal;
        D3DXVECTOR2 texture;
	};

	struct HeightMapType 
	{ 
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Terrain();
	Terrain(const Terrain&);
	~Terrain();

	bool Init(const string &hightMapFile, const string &path, const string &fileName);
	void Shutdown();

    ID3D11Buffer*const& GetVerticeBuffer() const;
    ID3D11Buffer*const& GetIndexBuffer() const;
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
    const XMMATRIX GetWorldMatrix() const;
private:
    //���ظ߶�ͼ�����������߶�
	bool LoadHeightMap(const string &);

    //��һ���߶�
	void NormalizeHeightMap();

    //�������㷨������
	bool CalculateNormals();

    //���ٸ߶�����
	void ShutdownHeightMap();

    //������������
	void CalculateTextureCoordinates();

    //���ص�������
	bool LoadTexture(const string &path, const string &filename);
	
    //�ͷŵ�������
    void ReleaseTexture();
    
    //�������㻺�����������
	bool InitializeBuffers(ID3D11Device*);

    //���ٻ���
	void ShutdownBuffers();
	
private:
	int terrainWidth, terrainHeight;
	int vertexCount, indexCount;
	ID3D11Buffer *vertexBuffer, *indexBuffer;
	HeightMapType* heightMap;
	Texture *texture;
};

#endif