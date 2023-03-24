#include "“Ù¿÷∫–.h"
#include "MonoSystem.h"
#include "GameVoice.h"
#include "coin.h"

void “Ù¿÷∫–::onCreate()
{
	type = UI;
	initAnimation(Musicbox,body.width,body.height);
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
	if (body.posx > 640 || body.posx < 0)
	{
		vx = -vx;
	}
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

