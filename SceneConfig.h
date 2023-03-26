#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include "head.h"

using namespace std;
// 配置全局变量与静态信息
class Sceneconfig
{
public:
	static Sceneconfig* GetInstance();
	int MaxFrame = 60;
private:
	Sceneconfig();
};

