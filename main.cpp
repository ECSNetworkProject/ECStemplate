#define _CRT_SECURE_NO_WARNINGS
#include <easyx.h>
#include "MonoSystem.h"
#include "head.h"
#include "SceneConfig.h"
#include <time.h>
#include "window.h"
using namespace easy2d;


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
    if (Game::init())
    {
        Renderer::showFps(true);
        // �޸Ĵ��ڱ���
        Window::setTitle("���շ��۶�ս��");
        // ����һ���ճ���
        Scene* scene = new Scene;
        // ���� scene ����
        SceneManager::enter(scene);
        // �ڳ����м���ؿ�������������ʹ��Easy2Dԭ���Ĺ���
        scene->addChild(MonoSystem::GetInstance());
        // easyx ��ʼ��
        InitMenu();
        // ��ʼ������
        Game::start();
        // �ͷ��ڴ�
        delete scene;
    }
    Game::destroy();
	return 0;
}
