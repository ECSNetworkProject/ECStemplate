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
    // 计算碰撞
    bool CrossLine(Rect r1, Rect r2);

    template <typename T>
    // 提取字符串中的数字
    int numberInStr(T temp, int startPos = 0, int range = 0);
#pragma region 字符类型转换
    string ws2s(const wstring& ws);

    wstring s2ws(const string& s);
    // 字符转换
    void Wchar_tToString(std::string& szDst, const wchar_t* wText);

    //不要忘记在使用完wchar_t*后delete[]释放内存
    wchar_t* multiByteToWideChar(const string& pKey);
#pragma endregion
    bool CmpAnimationFile(wstring a, wstring b);
    // 查找目录内包含指定名称的文件
    vector<wstring> FindAnimationFiles(string path, string containStr);
}