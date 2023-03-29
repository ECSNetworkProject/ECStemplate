#include "���ֺ�.h"
#include "MonoSystem.h"
#include "GameVoice.h"
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
	GameMusic("�ӷ�.wav");
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
	if (IsOpen)
	{
		// ����ʣ�����
		int temp = leaveTime - GetTickCount64() + startTime;
		// ʱ�䵽�˹ر�����
		if (temp < 0)
		{
			IsOpen = false;
			return;
		}
		
	}

}

void ���ֺ�::ToggleMusic()
{
	IsOpen = !IsOpen;
	if (IsOpen)
	{
		leaveTime = GameMusic(NowMusic);
		startTime = GetTickCount64();
	}
	else CloseMusic(NowMusic);
}

void ���ֺ�::onCrash(MonoObject* collider)
{
	if (!canThrough) vx = -vx;
}

