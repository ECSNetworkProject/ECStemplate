#pragma once
#include "button.h"
#include"NetworkObject.h"

class �������:public CustomButton, public NetworkObject
{
	void onCreate();
	void onClick();
	void GetNetworkMessage(string message);
};

