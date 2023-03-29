#pragma once
#include "button.h"

// ¡‚–ŒºÃ≥–
class “Ù¿÷∫– :public CustomButton
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

