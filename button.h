#pragma once
#include <iostream>
#include "MonoObject.h"
using namespace std;
class CustomButton :virtual public MonoObject
{
public:
	CustomButton();
	const wchar_t* Text=L"";
	void onFrameUpdate();
	void onGetMessage(ExMessage message);
	// 按钮被点击时调用
	virtual void onClick();
};
