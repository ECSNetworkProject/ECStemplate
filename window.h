#pragma once
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
	// ��¼���ֺ�ָ�������ֺ�״̬
	vector<���ֺ�*> musicboxes;
	// ��¼���������ֺ�
	���ֺ�* openingMusicbox;
};