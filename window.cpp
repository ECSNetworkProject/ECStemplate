#include "Window.h"
#include "Button.h"
#include "MonoSystem.h"
#include "“Ù¿÷∫–.h"

void GameWindow::onCreate()
{
	canThrough = true;
}


void GameWindow::menu()
{
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/ø™ ºΩÁ√Ê±≥æ∞.jpg"), body.width, body.height);
	“Ù¿÷∫–* musicBox = CreateObject<“Ù¿÷∫–>(Utils::Rect{ 110,310,100, 100 });
	musicBox->Text = L"“Ù¿÷∫–";
	musicBox->NowMusic = "mysoul.mp3";
	musicBox = CreateObject<“Ù¿÷∫–>(Utils::Rect{ 270,310,100, 100 });
	musicBox->Text = L"“Ù¿÷∫–";
	musicBox->NowMusic = "somewhere.mp3";
	musicBox = CreateObject<“Ù¿÷∫–>(Utils::Rect{ 430,310,100, 100 });
	musicBox->Text = L"“Ù¿÷∫–";
	musicBox->NowMusic = "»’Œƒ.mp3";
}

void GameWindow::onFrameUpdate()
{
	putimage(0, 0, &img1);
}

