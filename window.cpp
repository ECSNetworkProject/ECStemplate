#include "Window.h"
#include "Button.h"
#include "MonoSystem.h"
#include "音乐盒.h"

void GameWindow::onCreate()
{
	canThrough = true;
}


void GameWindow::musicMenu()
{
	initgraph(getSize().width, getSize().height, EX_SHOWCONSOLE);
	Window::setSize(getSize().width, getSize().height);
	// easy2d
	auto img = gcnew Sprite();
	bool check = img->open("Image/开始界面背景.jpg");
	img->setSize(getSize().width, getSize().height);
	this->addChild(img);
	// easyx;
	loadimage(&img1, _T("./Image/开始界面背景.jpg"), getSize().width, getSize().height);
	// 创建音乐盒1
	音乐盒* musicBox = CreateObject<音乐盒>(Utils::Rect{ 110,310,100, 100 });
	musicBox->NowMusic = "mysoul.mp3";
	musicboxes.push_back(musicBox);
	// 创建音乐盒2
	musicBox = CreateObject<音乐盒>(Utils::Rect{ 270,310,100, 100 });
	musicBox->NowMusic = "somewhere.mp3";
	musicboxes.push_back(musicBox);
	// 创建音乐盒3
	musicBox = CreateObject<音乐盒>(Utils::Rect{ 430,310,100, 100 });
	musicBox->NowMusic = "日文.mp3";
	musicboxes.push_back(musicBox);
}

void GameWindow::onFrameUpdate()
{
	putimage(0, 0, &img1);
	for (int i = 0; i < musicboxes.size();i++) {
		// 如果出现音乐盒是开启状态并且不是当前记录的音乐盒
		if (musicboxes[i]->IsOpen == true && musicboxes[i] != openingMusicbox)
		{
			// 如果当前记录的音乐盒在播放，则关闭
			if (openingMusicbox!=nullptr && openingMusicbox->IsOpen) openingMusicbox->ToggleMusic();
			openingMusicbox = musicboxes[i];
		}
	}
}

