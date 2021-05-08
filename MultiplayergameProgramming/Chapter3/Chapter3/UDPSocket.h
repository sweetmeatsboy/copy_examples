#pragma once


class UDPSocket
{
private:
	friend class SocketUtil;
	SOCKET mSocket;
	UDPSocket(SOCKET _s) : mSocket(_s) {}
public:
	~UDPSocket();

	int Bind(const SocketAddress& _addr);
	int SendTo(const void* _send, int _len, const SocketAddress& _addr);
	int ReceiveFrom(void* _send, int _len, SocketAddress& _addr);

	int SetNonBlockingMode(bool _flag);
};

typedef shared_ptr<UDPSocket> UDPSocketPtr;
