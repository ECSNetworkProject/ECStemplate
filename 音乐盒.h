#pragma once
#include "button.h"
#include "AnimationManager.h"

// ���μ̳�
class ���ֺ� :public Button,AnimationManager
{
public:
	string NowMusic;
	void onCreate();
	void onClick();
	void onFrameUpdate();
	void ToggleMusic();
	bool IsOpen = false;
private:
	int leaveTime = 0;
	DWORD startTime;
};

