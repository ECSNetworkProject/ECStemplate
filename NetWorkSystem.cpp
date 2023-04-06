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

// ȫ�ֱ�������socket
SOCKET hSock;
// ȫ�ֱ����洢�����͵�����������Ϣ
queue<string> BoardingMessage;

// ���߳̽�����Ϣ
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

// ���̷߳�����Ϣ
inline unsigned SendMsg()
{
	// ���߳���ֻ�ܲ����ֲ�����
	char msg[1024];
	while (1)
	{
		if (BoardingMessage.size() > 0)
		{
			string temp = BoardingMessage.front();
			strcpy_s(msg, temp.c_str());
			BoardingMessage.pop();
			// ͣ��1ms,���ⷢ�ͳ����ַ���ճ��һ��
			std::this_thread::sleep_for(1ms);
			send(hSock, msg, strlen(msg), 0);
		}
	}
	return 0;
}

NetworkSystem* NetworkSystem::GetInstance()
{
	// ����ʽ
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
	// ��ȡʱ�䲢��ӵ��ַ�����
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
	// �ж����������ǲ���networkObject����ӵ���������
	vector<MonoObject*> objs = MonoSystem::GetInstance()->getNewObjects();
	for (int i = 0; i < objs.size(); i++)
	{
		NetworkObject* obj = dynamic_cast<NetworkObject*>(objs[i]);
		if (obj) networkObjects.push_back(obj);
	}
	// ȡ��һ��������Ϣ
	string message = PopNetworkMessage();
	// ����ǿ���Ϣ�򷵻�
	if (message == "") return;
	// ����������Ϣ
	for (int i = 0; i < networkObjects.size(); i++)
	{
		networkObjects[i]->GetNetworkMessage(message);
	}
}

bool NetworkSystem::Init()
{
	//��ʼ��socket����
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
		// ���socket����
		WSACleanup();
		return -1;
	}
	hSock = socket(AF_INET, SOCK_STREAM, 0);
	//�󶨶˿�
	SOCKADDR_IN servAdr;
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(9999); // �˿ں�
	inet_pton(AF_INET, "43.136.100.219", &servAdr.sin_addr); // ����IP��ַ

	//���ӷ�����
	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		printf("connect error : %d", GetLastError());
		return -1;
	}
	else
	{
		printf("�ɹ����ӵ�����,�����뱾������:");
		char msg[1024];
		scanf("%s", msg);
		send(hSock, msg, strlen(msg), 0);
	}

	//ѭ������Ϣ
	HANDLE hRecvHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvMsg, (void*)&hSock, 0, NULL);
	// ѭ����׽Ҫ���͵���Ϣ
	thread SendHand(SendMsg);
	SendHand.detach();
	// Э��debug��
	while (1)
	{
		printf("Э��DEBUGģʽ������������Э�����ݣ�\n");
		char msg[1024];
		memset(msg, 0, sizeof(msg));
		fgets(msg, 100, stdin);
		// -1��Ϊ�˺��Ի��з�
		send(hSock, msg, strlen(msg)-1, 0);
	}
	return true;
}

NetworkSystem::~NetworkSystem()
{
	WSACleanup();
	closesocket(hSock);
}