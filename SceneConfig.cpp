#include "SceneConfig.h"


Sceneconfig::Sceneconfig()
{
}

Sceneconfig* Sceneconfig::GetInstance()
{
	// ����ʽ
	static Sceneconfig m_Instance;
	return &m_Instance;
}
