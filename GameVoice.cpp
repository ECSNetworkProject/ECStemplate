#define _CRT_SECURE_NO_WARNINGS
#include"GameVoice.h"
#include<stdio.h>
#include<iostream>
#include<Windows.h>
#include<mmsystem.h>  
#include "Utils.h"
#include<string>
#pragma comment(lib,"winmm.lib")
using namespace std;
#include"GameVoice.h"

void OperatorMusic(wstring operater, string MusicName, int startPos)
{
	wchar_t MusicPath[1024];
	wcscpy(MusicPath, L""); //这句很重要，否则wcs会是乱码。
	wcscat(MusicPath, operater.c_str());
	wcscat(MusicPath, L" ./GameVoice/");
	wcscat(MusicPath, Utils::multiByteToWideChar(MusicName));
	if (startPos > 0)
	{
		// 将int类型转化为wstring类型
		std::wstring wstr = std::to_wstring(startPos);
		const wchar_t* warray = wstr.c_str();
		wcscat(MusicPath, L" from ");
		wcscat(MusicPath, wstr.c_str());
	}
	mciSendString(MusicPath, 0, 0, 0);
}

int MusicLength(string MusicName)
{
	// 计算音乐长度
	wchar_t st[100];
	wchar_t MusicPath[1024];
	wcscpy(st, L""); //这句很重要，否则wcs会是乱码。
	wcscpy(MusicPath, L""); //这句很重要，否则wcs会是乱码。
	wcscat(MusicPath, L"status  ./GameVoice/");
	wcscat(MusicPath, Utils::multiByteToWideChar(MusicName));
	wcscat(MusicPath, L" length");
	mciSendString(MusicPath, st, 100, NULL);
	return  _wtoi(st);
}

int GameMusic(string MusicName,int startPos)
{
	OperatorMusic(L"close", MusicName, startPos);
	OperatorMusic(L"open", MusicName, startPos);
	OperatorMusic(L"play", MusicName, startPos);
	return MusicLength(MusicName);
}

void CloseMusic(string MusicName)
{
	OperatorMusic(L"close", MusicName,0);
}


