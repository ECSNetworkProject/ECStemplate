#include "“Ù¿÷∫–.h"
#include "MonoSystem.h"
#include "GameVoice.h"
#include "coin.h"

void “Ù¿÷∫–::onCreate()
{
	CustomButton::onCreate();
	type = UI;
	vx = 100;
	canThrough = false;
}

void “Ù¿÷∫–::onClick()
{
	GameMusic("º”∑÷.wav");
	CreateObject<coin>({});
	canThrough = true;
	// «–ªªø™πÿ◊¥Ã¨
	ToggleMusic();
}

void “Ù¿÷∫–::onFrameUpdate()
{
	CustomButton::onFrameUpdate();
	// ◊Û”““∆∂Ø
	if (getPosX() > 640 || getPosX() < 0)
	{
		vx = -vx;
	}
	if (IsOpen)
	{
		// º∆À„ £”‡∫¡√Î
		int temp = leaveTime - GetTickCount64() + startTime;
		//  ±º‰µΩ¡Àπÿ±’“Ù¿÷
		if (temp < 0)
		{
			IsOpen = false;
			return;
		}
		
	}

}

void “Ù¿÷∫–::ToggleMusic()
{
	IsOpen = !IsOpen;
	if (IsOpen)
	{
		leaveTime = GameMusic(NowMusic);
		startTime = GetTickCount64();
	}
	else CloseMusic(NowMusic);
}

void “Ù¿÷∫–::onCrash(MonoObject* collider)
{
	if (!canThrough) vx = -vx;
}

