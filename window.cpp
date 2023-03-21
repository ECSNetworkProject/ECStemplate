#include "Window.h"
#include "Button.h"
#include "MonoSystem.h"
#include "���ֺ�.h"

void GameWindow::onCreate()
{
	canThrough = true;
}


void GameWindow::musicMenu()
{
	initgraph(body.width, body.height, EX_SHOWCONSOLE);
	loadimage(&img1, _T("./Image/��ʼ���汳��.jpg"), body.width, body.height);
	// �������ֺ�1
	���ֺ�* musicBox = CreateObject<���ֺ�>(Utils::Rect{ 110,310,100, 100 });
	musicBox->Text = L"���ֺ�";
	musicBox->NowMusic = "mysoul.mp3";
	musicboxes.push_back(musicBox);
	// �������ֺ�2
	musicBox = CreateObject<���ֺ�>(Utils::Rect{ 270,310,100, 100 });
	musicBox->Text = L"���ֺ�";
	musicBox->NowMusic = "somewhere.mp3";
	musicboxes.push_back(musicBox);
	// �������ֺ�3
	musicBox = CreateObject<���ֺ�>(Utils::Rect{ 430,310,100, 100 });
	musicBox->Text = L"���ֺ�";
	musicBox->NowMusic = "����.mp3";
	musicboxes.push_back(musicBox);
}

void GameWindow::onFrameUpdate()
{
	putimage(0, 0, &img1);
	for (int i = 0; i < musicboxes.size();i++) {
		// ����������ֺ��ǿ���״̬���Ҳ��ǵ�ǰ��¼�����ֺ�
		if (musicboxes[i]->IsOpen == true && musicboxes[i] != openingMusicbox)
		{
			// �����ǰ��¼�����ֺ��ڲ��ţ���ر�
			if (openingMusicbox!=nullptr && openingMusicbox->IsOpen) openingMusicbox->ToggleMusic();
			openingMusicbox = musicboxes[i];
		}
	}
}

