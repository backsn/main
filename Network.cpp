#include "Standard.h"
#include <stdlib.h>
#include <stdio.h>

Network::Network()
{

}

Network::~Network()
{

}

void Network::Destroy()
{
	// closesocket()
	closesocket(listen_sock);
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
}

BOOL Network::Init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	return 1;
}

void Network::Bind()
{
	// bind()
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");
}

void Network::SetSocket()
{
	// socket()
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");
}

void Network::Setconnect()
{
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");
}

void Network::err_quit(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

void Network::err_display(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

void Network::Accept()
{
	while (1)
	{
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET)
		{
			//	err_display("accept()");
			continue;
		}
		/*	printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));*/
		Process();

		closesocket(client_sock);
		printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}
	Destroy();
}

void Network::Process()
{
	if (state == 0)
	{
		// 클라이언트와 데이터 통신
		while (1)
		{
			// 데이터 받기
			retval = recv(client_sock, buf, BUFSIZE, 0);
			if (retval == SOCKET_ERROR)
			{
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// 받은 데이터 출력
			buf[retval] = '\0';
			printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port), buf);

			// 데이터 보내기
			retval = send(client_sock, buf, retval, 0);
			if (retval == SOCKET_ERROR)
			{
				err_display("send()");
				break;
			}
		}
	}
	if (state == 1)
	{
		while (1)
		{
			// 데이터 입력
			ZeroMemory(buf, sizeof(buf));
			printf("\n[보낼 데이터] ");
			if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
				break;

			// '\n' 문자 제거
			len = strlen(buf);
			if (buf[len - 1] == '\n')
				buf[len - 1] = '\0';
			if (strlen(buf) == 0)
				break;

			// 데이터 보내기
			retval = send(sock, buf, strlen(buf), 0);
			if (retval == SOCKET_ERROR)
			{
				err_display("send()");
				break;
			}
			printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);

			// 데이터 받기
			retval = recvn(sock, buf, retval, 0);
			if (retval == SOCKET_ERROR)
			{
				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			// 받은 데이터 출력
			buf[retval] = '\0';
			printf("[TCP 클라이언트] %d바이트를 받았습니다.\n", retval);
			printf("[받은 데이터] %s\n", buf);
		}
	}
}

int Network::recvn(SOCKET s, char* buf, int len, int flags)
{
	return 1;
}
