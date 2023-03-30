#pragma once
#include<io.h>
#include <vector>
#include<iostream>
#include <string>
using namespace std;

namespace Utils {
    const float EQS = 1e-6;
    struct Rect
    {
        float posx, posy;
        float width, height;        // Point 2
    };
    // ������ײ
    bool CrossLine(Rect r1, Rect r2);

    template <typename T>
    // ��ȡ�ַ����е�����
    int numberInStr(T temp, int startPos = 0, int range = 0);
#pragma region �ַ�����ת��
    string ws2s(const wstring& ws);

    wstring s2ws(const string& s);
    // �ַ�ת��
    void Wchar_tToString(std::string& szDst, const wchar_t* wText);

    //��Ҫ������ʹ����wchar_t*��delete[]�ͷ��ڴ�
    wchar_t* multiByteToWideChar(const string& pKey);
#pragma endregion
    bool CmpAnimationFile(wstring a, wstring b);
    // ����Ŀ¼�ڰ���ָ�����Ƶ��ļ�
    vector<wstring> FindAnimationFiles(string path, string containStr);
}