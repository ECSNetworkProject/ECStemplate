#include "Window.h"
#include "Button.h"
#include "MonoSystem.h"
#include "���ֺ�.h"

void GameWindow::onCreate()
{
	canThrough = true;
}


void GameWindow::menu()
{
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/��ʼ���汳��.jpg"), body.width, body.height);
	���ֺ�* musicBox = CreateObject<���ֺ�>(Utils::Rect{ 110,310,100, 100 });
	musicBox->Text = L"���ֺ�";
	musicBox->NowMusic = "mysoul.mp3";
	musicBox = CreateObject<���ֺ�>(Utils::Rect{ 270,310,100, 100 });
	musicBox->Text = L"���ֺ�";
	musicBox->NowMusic = "somewhere.mp3";
	musicBox = CreateObject<���ֺ�>(Utils::Rect{ 430,310,100, 100 });
	musicBox->Text = L"���ֺ�";
	musicBox->NowMusic = "����.mp3";
}

void GameWindow::onFrameUpdate()
{
	putimage(0, 0, &img1);
}

