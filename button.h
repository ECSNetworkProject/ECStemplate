#pragma once
#include <iostream>
#include "MonoObject.h"
using namespace std;
class CustomButton :virtual public MonoObject
{
public:
	void onCreate();
	void onFrameUpdate();
	// ��ť�����ʱ����
	virtual void onClick();
	virtual ~CustomButton();
protected:
	ShapeNode* button;
	Text* text;
};
