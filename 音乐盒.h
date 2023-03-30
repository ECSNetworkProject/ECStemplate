#pragma once
#include "button.h"
#include"NetworkObject.h"
// ¡‚–ŒºÃ≥–
class “Ù¿÷∫– :public CustomButton,public NetworkObject
{
public:
	string NowMusic;
	void onCreate();
	void onClick();
	void onFrameUpdate();
	void ToggleMusic();
	void onCrash(MonoObject* collider);
	void GetNetworkMessage(string message);
	bool IsOpen = false;
private:
	int leaveTime = 0;
	DWORD startTime;
};

