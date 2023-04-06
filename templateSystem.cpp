#include "templateSystem.h"
#include "MonoSystem.h"

templateSystem* templateSystem::GetInstance()
{
	// ����ʽ
	static templateSystem m_Instance;
	return &m_Instance;
}

void templateSystem::Run()
{
	// �ж����������ǲ���templateObject����ӵ���������
	vector<MonoObject*> objs = MonoSystem::GetInstance()->getNewObjects();
	for (int i = 0; i < objs.size(); i++)
	{
		templateObject* obj = dynamic_cast<templateObject*>(objs[i]);
		if (obj) templateObjects.push_back(obj);
	}
}

bool templateSystem::Init()
{
	return true;
}

templateSystem::~templateSystem()
{
}