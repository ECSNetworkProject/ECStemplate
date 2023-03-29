#pragma once
#include <windows.h>
#include<io.h>
#include <vector>
#include<iostream>
#include <string>
#include <codecvt>
#include <comutil.h>  
#include <algorithm>
#pragma comment(lib, "comsuppw.lib")
using namespace std;

namespace Utils {
    const float EQS = 1e-6;
    struct Rect
    {
        float posx, posy;
        float width, height;        // Point 2
    };
    // ������ײ
    inline bool CrossLine(Rect r1, Rect r2)
    {

        float w = abs(r1.posx + r1.width / 2 - r2.posx - r2.width / 2);
        float h = abs(r1.posy + r1.height / 2 - r2.posy - r2.height / 2);

        if (w < (r1.width + r2.width) / 2 && h < (r1.height + r2.height) / 2)
            return true;
        else
            return false;
    }

    template <typename T>
    // ��ȡ�ַ����е�����
    inline int numberInStr(T temp, int startPos=0, int range=0)
    {
        int x = 0;
        if (range == 0) range = temp.length();
        for (int i = startPos; i < temp.length() && i < startPos + range; i++)
        {
            if (temp[i] >= '0' && temp[i] <= '9')
                x = x * 10 + temp[i] - '0';
        }
        return x;
    }
#pragma region �ַ�����ת��
    inline string ws2s(const wstring& ws)
    {
        _bstr_t t = ws.c_str();
        char* pchar = (char*)t;
        string result = pchar;
        return result;
    }

    inline wstring s2ws(const string& s)
    {
        _bstr_t t = s.c_str();
        wchar_t* pwchar = (wchar_t*)t;
        wstring result = pwchar;
        return result;
    }
    // �ַ�ת��
    inline void Wchar_tToString(std::string& szDst, const wchar_t* wText)
    {
        DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte������
        char* psText;  // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
        psText = new char[dwNum];
        WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte���ٴ�����
        szDst = psText;// std::string��ֵ
        delete[]psText;// psText�����
    }

    //��Ҫ������ʹ����wchar_t*��delete[]�ͷ��ڴ�
    inline wchar_t* multiByteToWideChar(const string& pKey)
    {
        auto pCStrKey = pKey.c_str();
        //��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
        int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
        wchar_t* pWCStrKey = new wchar_t[pSize];
        //�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
        MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
        return pWCStrKey;
    }
#pragma endregion
    inline bool CmpAnimationFile(wstring a, wstring b)
    {
        int x = numberInStr(a), y = numberInStr(a);
        return x < y;
    }
    // ����Ŀ¼�ڰ���ָ�����Ƶ��ļ�
    inline vector<wstring> FindAnimationFiles(string path,string containStr)
    {

        vector<wstring> rev;
        _finddata64i32_t fileInfo;
        intptr_t hFile = _findfirst((path + "/*.*").c_str(), &fileInfo);
        do
        {
            string fileName = fileInfo.name;
            int index=fileName.find(containStr);
            if (index < fileName.length())
            {
                // �ų�ĩβû�����ֵ��ļ�
                if (fileName[index + containStr.length()] < '0' ||
                    fileName[index + containStr.length()] >'9') continue;
                rev.push_back(s2ws(path+"/"+fileName));
            }

        } while (_findnext(hFile, &fileInfo) == 0);
        sort(rev.begin(), rev.end(),CmpAnimationFile);
        //�ر��ļ����  
        _findclose(hFile);
        return rev;
    }
}