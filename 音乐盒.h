#pragma once
#include "button.h"

// ���μ̳�
class ���ֺ� :public CustomButton
{
public:
	string NowMusic;
	void onCreate();
	void onClick();
	void onFrameUpdate();
	void ToggleMusic();
	void onCrash(MonoObject* collider);
	bool IsOpen = false;
private:
	int leaveTime = 0;
	DWORD startTime;
};

