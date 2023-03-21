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
	// ���ڿ���ÿ�����֡
	clock_t lastFrame = clock();
	int frameCnt = 0;
	int lastflag = 0;
	while (1)
	{
		// �̶�ʱ�������һ��
		if (clock() - lastFrame > frameCnt * 1000 / Sceneconfig::GetInstance()->MaxFrame)
		{
			
			FlushBatchDraw();//ֱ�������easyx������
			cleardevice();
			MonoSystem::GetInstance()->Run();
			frameCnt++;
			if (frameCnt == Sceneconfig::GetInstance()->MaxFrame)
			{
				frameCnt = 0;
				cout << Sceneconfig::GetInstance()->MaxFrame << "֡����ʱ��" << clock() - lastFrame << endl;
				lastFrame = clock();
			}
			// cout << "��" << frameCnt << "֡:" << clock() << endl;
		}
	}
	EndBatchDraw();//���Ƶ�easyx����
	return 0;
}
