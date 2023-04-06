#pragma once
#include "MonoObject.h"

class coin :public MonoObject
{
public:
	void onCreate();
	void onFrameUpdate();
private:
	Sprite* img;
};

