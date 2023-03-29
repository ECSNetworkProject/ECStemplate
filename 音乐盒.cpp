#include "���ֺ�.h"
#include "MonoSystem.h"
#include "coin.h"

void ���ֺ�::onCreate()
{
	CustomButton::onCreate();
	type = UI;
	vx = 100;
	canThrough = false;
}

void ���ֺ�::onClick()
{
	// GameMusic("�ӷ�.wav");
	CreateObject<coin>({});
	canThrough = true;
	// �л�����״̬
	ToggleMusic();
}

void ���ֺ�::onFrameUpdate()
{
	CustomButton::onFrameUpdate();
	// �����ƶ�
	if (getPosX() > 640 || getPosX() < 0)
	{
		vx = -vx;
	}

}

void ���ֺ�::ToggleMusic()
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

void ���ֺ�::onCrash(MonoObject* collider)
{
	if (!canThrough) vx = -vx;
}

