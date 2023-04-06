#include "音乐盒.h"
#include "MonoSystem.h"
#include"NetWorkSystem.h"
#include "coin.h"


void 音乐盒::onCreate()
{
	CustomButton::onCreate();
	type = UI;
	vx = 100;
	canThrough = false;
}

void 音乐盒::onClick()
{
	// GameMusic("加分.wav");
	CreateObject<coin>({});
	canThrough = true;
	NetworkSystem::GetInstance()->AppendNetworkMessage("点击音乐盒", true);
	// 切换开关状态
	ToggleMusic();
}

void 音乐盒::onFrameUpdate()
{
	CustomButton::onFrameUpdate();
	// 左右移动
	if (getPosX() > 640 || getPosX() < 0)
	{
		vx = -vx;
	}

}

void 音乐盒::ToggleMusic()
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

void 音乐盒::onCrash(MonoObject* collider)
{
	if (!canThrough) vx = -vx;
}

void 音乐盒::GetNetworkMessage(string message)
{
}

