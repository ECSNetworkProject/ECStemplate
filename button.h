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
	// ��ť�����ʱ����
	virtual void onClick();
};
