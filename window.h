#pragma once
#include <easyx.h>
#include <vector>
#include "Button.h"
#include "Utils.h"
#include "���ֺ�.h"

class GameWindow:public MonoObject
{
public:
	void onCreate();
	void musicMenu();
	void onFrameUpdate();
private:
	IMAGE img1;
	// ��¼���ֺ�ָ�������ֺ�״̬
	vector<���ֺ�*, bool> musicboxes;
	// ��¼���������ֺ�
	���ֺ�* openingMusicbox;
};