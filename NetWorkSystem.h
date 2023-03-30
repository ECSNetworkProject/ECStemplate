#pragma once
#include <iostream>
#include <queue>
#include "NetworkObject.h"
using namespace std;

/// <summary>
/// 用于获取网络信息
/// </summary>

class NetworkSystem
{
public:
	static NetworkSystem* GetInstance();
	/// <summary>
	/// 取出一条收到的网络消息
	/// </summary>
	string PopNetworkMessage();
	/// <summary>
	/// 添加一条网络消息,是否广播到所有其他客户端
	/// </summary>
	void AppendNetworkMessage(string message, bool board);
	/// <summary>
	/// 网络系统帧更新
	/// </summary>
	void Run();
	bool Init();
	~NetworkSystem();
private:
	NetworkSystem() = default;
	// 存储所有网络物体
	vector<NetworkObject*> networkObjects;
	//保存消息队列
	queue<string> networkMessage;
};