#pragma once
#include <iostream>
#include "MonoObject.h"
using namespace std;
class Button :virtual public MonoObject
{
public:
	Button();
	const wchar_t* Text=L"";
	void onFrameUpdate();
	void onGetMessage(ExMessage message);
	// ��ť�����ʱ����
	virtual void onClick();
};
