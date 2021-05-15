#pragma once

class UDPSocket
{
private:
	friend class SocketUtil;
	UDPSocket(SOCKET _s) :mSocket(_s)
	{
	}
	SOCKET mSocket;
public:
	~UDPSocket();
	int Bind(const SocketAddress& _addr);
	int SendTo(const void* _data, int _len, const SocketAddress& _addr);
	int ReceiveFrom(void* _data, int _len, const SocketAddress& _addr);
	int SetNonBlockingMode(bool _flag);
};

typedef shared_ptr<UDPSocket> UDPSocketPtr;