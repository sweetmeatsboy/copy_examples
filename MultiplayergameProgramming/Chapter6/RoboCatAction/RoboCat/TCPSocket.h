#pragma once


class TCPSocket
{
private :
	SOCKET mSocket;
	friend class SocketUtil;
	TCPSocket(SOCKET _s) 
		: mSocket(_s)
	{
	}
public:
	~TCPSocket();
	int Connect(const SocketAddress& _addr);
};

typedef shared_ptr<TCPSocket> TCPSocketPtr;