#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "NetworkSystem.h"
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <cstdio>
#include <thread>
#include "MonoObject.h"
#include "MonoSystem.h"
#include "NetworkObject.h"
#pragma comment(lib, "ws2_32.lib")

// 全局变量创建socket
SOCKET hSock;
// 全局变量存储待发送到服务器的消息
queue<string> BoardingMessage;

// 多线程接收消息
inline unsigned RecvMsg(void* arg)
{
	SOCKET sock = *((SOCKET*)arg);
	char msg[1024];
	while (1)
	{
		int len = recv(sock, msg, sizeof(msg) - 1, 0);
		if (len == -1)
		{
			cout << WSAGetLastError() << endl;
			return -1;
		}
		msg[len] = '\0';
		NetworkSystem::GetInstance()->AppendNetworkMessage(msg, false);
		printf("%s\n", msg);
	}
	return 0;
}

// 多线程发送消息
inline unsigned SendMsg()
{
	// 多线程内只能操作局部变量
	char msg[1024];
	while (1)
	{
		if (BoardingMessage.size() > 0)
		{
			string temp = BoardingMessage.front();
			strcpy_s(msg, temp.c_str());
			BoardingMessage.pop();
			// 停顿1ms,避免发送出的字符串粘在一起
			std::this_thread::sleep_for(1ms);
			send(hSock, msg, strlen(msg), 0);
		}
	}
	return 0;
}

NetworkSystem* NetworkSystem::GetInstance()
{
	// 饿汉式
	static NetworkSystem m_Instance;
	return &m_Instance;
}


string NetworkSystem::PopNetworkMessage()
{
	if (networkMessage.size() == 0) return "";
	string msg = networkMessage.front();
	networkMessage.pop();
	return msg;
}

void NetworkSystem::AppendNetworkMessage(string message, bool board)
{
	// 获取时间并添加到字符串中
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	message += "-" + to_string(st.wSecond * 1000 + st.wMilliseconds);
	char msg[1024];
	strcpy_s(msg, message.c_str());
	networkMessage.push(msg);
	if (board)
	{
		BoardingMessage.push(msg);
	}
}

void NetworkSystem::Run()
{
	// 判断新增物体是不是networkObject并添加到自身数组
	vector<MonoObject*> objs = MonoSystem::GetInstance()->getNewObjects();
	for (int i = 0; i < objs.size(); i++)
	{
		NetworkObject* obj = dynamic_cast<NetworkObject*>(objs[i]);
		if (obj) networkObjects.push_back(obj);
	}
	// 取出一条网络消息
	string message = PopNetworkMessage();
	// 如果是空消息则返回
	if (message == "") return;
	// 发送网络消息
	for (int i = 0; i < networkObjects.size(); i++)
	{
		networkObjects[i]->GetNetworkMessage(message);
	}
}

bool NetworkSystem::Init()
{
	//初始化socket环境
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		// 清除socket环境
		WSACleanup();
		return -1;
	}
	hSock = socket(AF_INET, SOCK_STREAM, 0);
	//绑定端口
	SOCKADDR_IN servAdr;
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(9999); // 端口号
	inet_pton(AF_INET, "43.136.100.219", &servAdr.sin_addr); // 公网IP地址

	//连接服务器
	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		printf("connect error : %d", GetLastError());
		return -1;
	}
	else
	{
		printf("成功连接到网络,请输入本机姓名:");
		char msg[1024];
		scanf("%s", msg);
		send(hSock, msg, strlen(msg), 0);
	}

	//循环收消息
	HANDLE hRecvHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvMsg, (void*)&hSock, 0, NULL);
	// 循环捕捉要发送的消息
	thread SendHand(SendMsg);
	SendHand.detach();
	return true;
}

NetworkSystem::~NetworkSystem()
{
	WSACleanup();
	closesocket(hSock);
}