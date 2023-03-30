#pragma once
#include "MonoObject.h"
class NetworkObject :
    virtual public MonoObject
{
public:
    NetworkObject();
    virtual void GetNetworkMessage(string message);
    virtual ~NetworkObject();
};