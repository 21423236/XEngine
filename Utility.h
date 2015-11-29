#ifndef __UTILITY__
#define __UTILITY__

#include "PreHeader.h"

template<typename T>
T MyMax(const T &a, const T &b)
{
    return a < b ? b : a;
}

template<typename T>
T MyMin(const T &a, const T &b)
{
    return a < b ? a : b;
}

//ɾ��һ��new�����Ķ���
template<typename T>
void SafeDelete(T &p)
{
    if(p != NULL)
    {
        delete p;
        p = NULL;
    }
}

//ɾ��new����������
template<typename T>
void ReleasNewArray(T *&p)
{
    if(p != NULL)
    {
        delete[] p;
        p = NULL;
    }
}

//ɾ��COM���
template<typename T>
inline void SafeRelease(T &t)
{
	if(t)
	{
		t->Release();
		t = NULL;
	}
}

//������ֵ�ض���ĳһ��Χ��
template<typename T>
inline T Clamp(T vMin, T vMax, T value)
{
	value = max(vMin,value);
	value = min(vMax,value);

	return value;
}

inline XMMATRIX InverseTranspose(CXMMATRIX m)
{
	XMMATRIX tmp = m;
	tmp.r[3] = XMVectorSet(0.f,0.f,0.f,1.f);
	
	return XMMatrixTranspose(XMMatrixInverse(&XMMatrixDeterminant(tmp),tmp));
}

//������ɫ
namespace Colors
{
	const XMVECTORF32 White     = {1.0f, 1.0f, 1.0f, 1.0f};
	const XMVECTORF32 Black     = {0.0f, 0.0f, 0.0f, 1.0f};
	const XMVECTORF32 Red       = {1.0f, 0.0f, 0.0f, 1.0f};
	const XMVECTORF32 Green     = {0.0f, 1.0f, 0.0f, 1.0f};
	const XMVECTORF32 Blue      = {0.0f, 0.0f, 1.0f, 1.0f};
	const XMVECTORF32 Yellow    = {1.0f, 1.0f, 0.0f, 1.0f};
	const XMVECTORF32 Cyan      = {0.0f, 1.0f, 1.0f, 1.0f};
	const XMVECTORF32 Magenta   = {1.0f, 0.0f, 1.0f, 1.0f};
	const XMVECTORF32 Silver	= {0.75f,0.75f,0.75f,1.0f};
};

inline wstring StrToWstr(const string& str)
{
    wstring ans(str.begin(), str.end());
    return ans;
}

inline string LPCWSTRToStr(const LPCWSTR& str)
{
    string ans = CW2A(str);
    return ans;
}

#endif