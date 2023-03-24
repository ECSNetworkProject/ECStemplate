#include "���ֺ�.h"
#include "MonoSystem.h"
#include "GameVoice.h"
#include "coin.h"

void ���ֺ�::onCreate()
{
	type = UI;
	initAnimation(Musicbox,body.width,body.height);
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
	if (body.posx > 640 || body.posx < 0)
	{
		vx = -vx;
	}
	if (IsOpen)
	{
		playAnimation(body.posx, body.posy);
		// ����ʣ�����
		int temp = leaveTime - GetTickCount64() + startTime;
		// ʱ�䵽�˹ر�����
		if (temp < 0)
		{
			IsOpen = false;
			return;
		}
		// ������ʾ��ʱ���
		string timeStamp;
		timeStamp += to_string(temp / 60000);
		timeStamp += ":" + to_string(temp % 60000 / 1000);
		const wchar_t* strTime = Utils::multiByteToWideChar(timeStamp);
		int textWide = textwidth(strTime);
		int textHeight = textheight(strTime);
		outtextxy(body.posx + (body.width - textWide) / 2,
			body.posy + (body.height - textHeight) / 4, strTime);
		
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

