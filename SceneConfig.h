#pragma once
#include "head.h"
#include <fstream>
#include <iostream>
#include "head.h"

using namespace std;
// ����ȫ�ֱ����뾲̬��Ϣ
class Sceneconfig
{
public:
	static Sceneconfig* GetInstance();
	int MaxFrame = 60;
private:
	Sceneconfig();
};

