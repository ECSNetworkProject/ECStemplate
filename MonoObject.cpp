#include "MonoObject.h"

int MonoObject::GetHashID()
{
	return hashId;
}


void MonoObject::onCreate()
{
}

void MonoObject::onCrash(MonoObject* collider)
{
}


void MonoObject::onFrameUpdate()
{
}

void MonoObject::onGetMessage(ExMessage message)
{
}

MonoObject::~MonoObject()
{
	cout << "基类部分清除" << endl;
}
