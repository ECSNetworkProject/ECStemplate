#pragma once
#include <iostream>
#include <queue>
using namespace std;

/// <summary>
/// ���ڻ�ȡ������Ϣ
/// </summary>

class NetworkSystem
{
public:
	static NetworkSystem* GetInstance();
	/// <summary>
	/// ȡ��һ���յ���������Ϣ
	/// </summary>
	string PopNetworkMessage();
	/// <summary>
	/// ���һ��������Ϣ,�Ƿ�㲥�����������ͻ���
	/// </summary>
	void AppendNetworkMessage(string message, bool board);
	/// <summary>
	/// ����ϵͳ֡����
	/// </summary>
	void Run();
	bool Init();
	~NetworkSystem();
private:
	NetworkSystem() = default;
	//������Ϣ����
	queue<string> networkMessage;
};