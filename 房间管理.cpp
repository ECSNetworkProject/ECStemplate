#include "�������.h"
#include "NetWorkSystem.h"

void �������::onCreate()
{
	CustomButton::onCreate();
	text->setText("��������");
}

void �������::onClick()
{
	cout << "��������" << endl;
	NetworkSystem::GetInstance()->AppendNetworkMessage("CreateRoom 1", true);
}

void �������::GetNetworkMessage(string message)
{
}
