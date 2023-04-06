#include "“Ù¿÷∫–.h"
#include "MonoSystem.h"
#include"NetWorkSystem.h"
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
	// GameMusic("º”∑÷.wav");
	CreateObject<coin>({});
	canThrough = true;
	NetworkSystem::GetInstance()->AppendNetworkMessage("µ„ª˜“Ù¿÷∫–", true);
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

}

void “Ù¿÷∫–::ToggleMusic()
{
	IsOpen = !IsOpen;
	if (IsOpen)
	{
		button->setFillColor(Color::Blue);
		// leaveTime = GameMusic(NowMusic);
		// startTime = GetTickCount64();
	}
	else
	{
		button->setFillColor(Color::Gray);
	}
}

void “Ù¿÷∫–::onCrash(MonoObject* collider)
{
	if (!canThrough) vx = -vx;
}

void “Ù¿÷∫–::GetNetworkMessage(string message)
{
}

