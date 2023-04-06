﻿#define _CRT_SECURE_NO_WARNINGS
#include "MonoSystem.h"
#include "NetWorkSystem.h"
#include "head.h"
#include "SceneConfig.h"
#include <time.h>
#include "window.h"
#include "templateSystem.h"
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

    // 打印csv表格数据
    templateSystem ::GetInstance()->Init();
    // 连接网络
    NetworkSystem::GetInstance()->Init();
    if (Game::init())
    {
        Renderer::showFps(true);
        // 修改窗口标题
        Window::setTitle("明日方舟对战版");
        // 创建一个空场景
        Scene* scene = new Scene;
        // 进入 scene 场景
        SceneManager::enter(scene);
        // 在场景中加入关卡管理器，而不使用Easy2D原本的管理
        scene->addChild(MonoSystem::GetInstance());
        // 初始化菜单
        InitMenu();
        // 初始化窗口
        Game::start();
        // 释放内存
        delete scene;
    }
    Game::destroy();
	return 0;
}
