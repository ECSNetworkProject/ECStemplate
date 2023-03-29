#pragma once
#include <iostream>
#include "MonoObject.h"
using namespace std;
class CustomButton :virtual public MonoObject
{
public:
	void onCreate();
	void onFrameUpdate();
	// 按钮被点击时调用
	virtual void onClick();
	virtual ~CustomButton();
protected:
	ShapeNode* button;
	Text* text;
};
