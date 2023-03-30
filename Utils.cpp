#pragma once
#include"Utils.h"
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
    // 计算碰撞
    bool CrossLine(Rect r1, Rect r2)
    {

        float w = abs(r1.posx + r1.width / 2 - r2.posx - r2.width / 2);
        float h = abs(r1.posy + r1.height / 2 - r2.posy - r2.height / 2);

        if (w < (r1.width + r2.width) / 2 && h < (r1.height + r2.height) / 2)
            return true;
        else
            return false;
    }

    template <typename T>
    // 提取字符串中的数字
    int numberInStr(T temp, int startPos , int range )
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
#pragma region 字符类型转换
    string ws2s(const wstring& ws)
    {
        _bstr_t t = ws.c_str();
        char* pchar = (char*)t;
        string result = pchar;
        return result;
    }

    wstring s2ws(const string& s)
    {
        _bstr_t t = s.c_str();
        wchar_t* pwchar = (wchar_t*)t;
        wstring result = pwchar;
        return result;
    }
    // 字符转换
    void Wchar_tToString(std::string& szDst, const wchar_t* wText)
    {
        DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);//WideCharToMultiByte的运用
        char* psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
        psText = new char[dwNum];
        WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);//WideCharToMultiByte的再次运用
        szDst = psText;// std::string赋值
        delete[]psText;// psText的清除
    }

    //不要忘记在使用完wchar_t*后delete[]释放内存
    wchar_t* multiByteToWideChar(const string& pKey)
    {
        auto pCStrKey = pKey.c_str();
        //第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
        int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
        wchar_t* pWCStrKey = new wchar_t[pSize];
        //第二次调用将单字节字符串转换成双字节字符串
        MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
        return pWCStrKey;
    }
#pragma endregion
    bool CmpAnimationFile(wstring a, wstring b)
    {
        int x = numberInStr(a), y = numberInStr(a);
        return x < y;
    }
    // 查找目录内包含指定名称的文件
    vector<wstring> FindAnimationFiles(string path, string containStr)
    {

        vector<wstring> rev;
        _finddata64i32_t fileInfo;
        intptr_t hFile = _findfirst((path + "/*.*").c_str(), &fileInfo);
        do
        {
            string fileName = fileInfo.name;
            int index = fileName.find(containStr);
            if (index < fileName.length())
            {
                // 排除末尾没有数字的文件
                if (fileName[index + containStr.length()] < '0' ||
                    fileName[index + containStr.length()] >'9') continue;
                rev.push_back(s2ws(path + "/" + fileName));
            }

        } while (_findnext(hFile, &fileInfo) == 0);
        sort(rev.begin(), rev.end(), CmpAnimationFile);
        //关闭文件句柄  
        _findclose(hFile);
        return rev;
    }
}