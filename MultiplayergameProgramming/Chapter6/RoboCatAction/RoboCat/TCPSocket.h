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

	int Bind(const SocketAddress& _addr);
	int Listen(int _backLog = 32);
	shared_ptr<TCPSocket> Accept(SocketAddress& _addr);
	int32_t Send(const void* _data, size_t _len);
	int32_t Receive(void* _data, size_t _len);
};

typedef shared_ptr<TCPSocket> TCPSocketPtr;