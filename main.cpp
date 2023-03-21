#define _CRT_SECURE_NO_WARNINGS
#include <easyx.h>
#include "MonoSystem.h"
#include "head.h"
#include "SceneConfig.h"
#include <time.h>
#include "window.h"



void clearAllObject()
{
	vector<MonoObject*> objs = MonoSystem::GetInstance()->getAllObjects();
	for (int i = 0; i < objs.size(); i++) DestroyObject(objs[i]);
}

void InitMenu()
{
	clearAllObject();
	GameWindow* window=CreateObject<GameWindow>(Utils::Rect{ 0,0,640, 480 });
	window->musicMenu();
}

int main(void)
{
	InitMenu();
	BeginBatchDraw();
	// 用于控制每秒多少帧
	clock_t lastFrame = clock();
	int frameCnt = 0;
	int lastflag = 0;
	while (1)
	{
		// 固定时间戳运行一次
		if (clock() - lastFrame > frameCnt * 1000 / Sceneconfig::GetInstance()->MaxFrame)
		{
			
			FlushBatchDraw();//直接输出到easyx窗口中
			cleardevice();
			MonoSystem::GetInstance()->Run();
			frameCnt++;
			if (frameCnt == Sceneconfig::GetInstance()->MaxFrame)
			{
				frameCnt = 0;
				cout << Sceneconfig::GetInstance()->MaxFrame << "帧运行时间" << clock() - lastFrame << endl;
				lastFrame = clock();
			}
			// cout << "第" << frameCnt << "帧:" << clock() << endl;
		}
	}
	EndBatchDraw();//绘制到easyx窗口
	return 0;
}
