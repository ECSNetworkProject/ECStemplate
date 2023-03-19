#include "“Ù¿÷∫–.h"
#include "MonoSystem.h"
#include "GameVoice.h"
#include "coin.h"

void “Ù¿÷∫–::onCreate()
{
	type = UI;
	initAnimation(Music,body.width,body.height);
}

void “Ù¿÷∫–::onClick()
{
	cout << "“Ù¿÷∫–±ªµ„ª˜" << endl;
	GameMusic("º”∑÷.wav");
	CreateObject<coin>({});
	IsOpen = !IsOpen;
	if (IsOpen)
	{
		leaveTime = GameMusic(NowMusic);
		startTime = GetTickCount64();
	}
	else CloseMusic(NowMusic);
}

void “Ù¿÷∫–::onFrameUpdate()
{
	Button::onFrameUpdate();
	if (IsOpen)
	{
		playAnimation(body.posx, body.posy);
		// º∆À„ £”‡∫¡√Î
		int temp = leaveTime - GetTickCount64() + startTime;
		//  ±º‰µΩ¡Àπÿ±’“Ù¿÷
		if (temp < 0)
		{
			IsOpen = false;
			return;
		}
		// º∆À„œ‘ æµƒ ±º‰¥¡
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

