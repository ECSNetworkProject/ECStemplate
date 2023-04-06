#include "SceneConfig.h"



Sceneconfig::Sceneconfig()
{
}

Sceneconfig* Sceneconfig::GetInstance()
{
	// 饿汉式
	static Sceneconfig m_Instance;
	return &m_Instance;
}
