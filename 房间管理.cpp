#include "房间管理.h"
#include "NetWorkSystem.h"


void 房间管理::onCreate()
{
	CustomButton::onCreate();
	text->setText("创建房间");
}

void 房间管理::onClick()
{
	cout << "创建房间" << endl;
	NetworkSystem::GetInstance()->AppendNetworkMessage("CreateRoom 1", true);
}

void 房间管理::GetNetworkMessage(string message)
{
}
