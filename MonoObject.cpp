#include "MonoObject.h"

Utils::Rect MonoObject::GetBody()
{
	return Utils::Rect{ getPosX(),getPosY()  ,getSize().width,getSize().height};
}

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
	cout << "���ಿ�����" << endl;
}
