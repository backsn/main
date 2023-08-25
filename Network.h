#ifndef __NETWORK__
#define __NETWORK__

#define BUFSIZE 512

class Network
{
public:
	Network();
	~Network();

	BOOL Init();
	void Destroy();
	void Bind();
	void Accept();

	void SetSocket();
	void Setconnect();

	int recvn(SOCKET s, char* buf, int len, int flags);

	void err_quit(char* msg);
	void err_display(char* msg);

	void Process();

private:
	int retval;
	int len;

	int state; // 0 host 1 conecter		

	WSADATA wsa;
	SOCKADDR_IN serveraddr;
	SOCKET listen_sock;

	SOCKET sock;

	int addrlen;
	char buf[BUFSIZE + 1];
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
};

#endif