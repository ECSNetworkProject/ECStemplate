#pragma once
#include <easyx.h>
#include "Button.h"
#include "Utils.h"
class GameWindow:public MonoObject
{
public:
	void onCreate();
	void menu();
	void onFrameUpdate();
private:
	IMAGE img1;
};