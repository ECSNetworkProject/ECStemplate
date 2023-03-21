#include "���ֺ�.h"
#include "MonoSystem.h"
#include "GameVoice.h"
#include "coin.h"

void ���ֺ�::onCreate()
{
	type = UI;
	initAnimation(Music,body.width,body.height);
}

void ���ֺ�::onClick()
{
	cout << "���ֺб����" << endl;
	GameMusic("�ӷ�.wav");
	CreateObject<coin>({});
	// �л�����״̬
	ToggleMusic();
}

void ���ֺ�::onFrameUpdate()
{
	Button::onFrameUpdate();
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

