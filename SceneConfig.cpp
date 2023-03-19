#include "SceneConfig.h"


Sceneconfig::Sceneconfig()
{
}

Sceneconfig* Sceneconfig::GetInstance()
{
	// ¶öººÊ½
	static Sceneconfig m_Instance;
	return &m_Instance;
}
