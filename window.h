#pragma once
#include <vector>
#include "Button.h"
#include "Utils.h"
#include "音乐盒.h"


class GameWindow:public MonoObject
{
public:
	void onCreate();
	void musicMenu();
	void onFrameUpdate();
private:
	// 记录音乐盒指针与音乐盒状态
	vector<音乐盒*> musicboxes;
	// 记录开启的音乐盒
	音乐盒* openingMusicbox;
};