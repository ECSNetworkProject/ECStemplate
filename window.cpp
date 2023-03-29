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
	Window::setSize(getSize().width, getSize().height);
	// easy2d
	auto img = gcnew Sprite();
	bool check = img->open("Image/��ʼ���汳��.jpg");
	img->setSize(getSize().width, getSize().height);
	this->addChild(img);
	// �������ֺ�1
	���ֺ�* musicBox = CreateObject<���ֺ�>(Utils::Rect{ 110,310,100, 100 });
	musicBox->NowMusic = "mysoul.mp3";
	musicboxes.push_back(musicBox);
	// �������ֺ�2
	musicBox = CreateObject<���ֺ�>(Utils::Rect{ 270,310,100, 100 });
	musicBox->NowMusic = "somewhere.mp3";
	musicboxes.push_back(musicBox);
	// �������ֺ�3
	musicBox = CreateObject<���ֺ�>(Utils::Rect{ 430,310,100, 100 });
	musicBox->NowMusic = "����.mp3";
	musicboxes.push_back(musicBox);
}

void GameWindow::onFrameUpdate()
{
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

