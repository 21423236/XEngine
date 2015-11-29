#ifndef __SRVBATCH__
#define __SRVBATCH__

#include "PreHeader.h"

class SRVBatch
{
private:
    vector<ID3D11ShaderResourceView*>   shaderResourceViewTable;
    map<string, int>    name2IndexTable;
    static ID3D11ShaderResourceView *m_pRandomTexture;
public:
    ~SRVBatch();
    
    //����
    static SRVBatch* GetInstance();

    //���һ����Ⱦ��Դ��ͼ
    int AddSRV(const string& , ID3D11ShaderResourceView* );

    //ͨ�����ֻ�ȡһ����Ⱦ��Դ��ͼ
    ID3D11ShaderResourceView* GetSRVByName(const string& );

    //ͨ��������ȡһ����Ⱦ��Դ��ͼ
    ID3D11ShaderResourceView* GetSRVByIndex(int );

    //����һ����Ⱦ��Դ��ͼ
    ID3D11ShaderResourceView* LoadSRV(const string& , const string& );

    //����һ�������һά����
    ID3D11ShaderResourceView* GetRandomSRV1D();

    //���
    void Clear();

private:
    SRVBatch(){};
};

#endif