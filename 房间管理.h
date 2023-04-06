#pragma once
#include "button.h"
#include"NetworkObject.h"

class 房间管理:public CustomButton, public NetworkObject
{
	void onCreate();
	void onClick();
	void GetNetworkMessage(string message);
};

