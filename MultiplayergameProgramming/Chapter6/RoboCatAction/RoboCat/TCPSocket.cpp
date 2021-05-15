#include "stdafx.h"

int TCPSocket::Connect(const SocketAddress& _addr)
{
	int err = connect(mSocket, &_addr.mSockAddr, _addr.GetSize());
	if (err < 0)
	{
		SocketUtil::ReportError("TCPSocket::Connect");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Listen(int _backLog)
{
	int err = listen(mSocket, _backLog);
	if (err < 0)
	{
		SocketUtil::ReportError("TCPSocket::Listen");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& _addr)
{
	socklen_t len = _addr.GetSize();
	SOCKET nSock = accept(mSocket, &_addr.mSockAddr, &len);
	if (nSock!= INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(nSock));
	SocketUtil::ReportError("TCPSocket::Accept");
	return nullptr;
}


int32_t TCPSocket::Send(const void* _data, size_t _len)
{
	int sentCnt = send(mSocket, static_cast<const char*>(_data), _len, 0);
	if (sentCnt < 0)
	{
		SocketUtil::ReportError("TCPSocket::Send");
		return -SocketUtil::GetLastError();
	}
	return sentCnt;
}

int32_t TCPSocket::Receive(void* _data, size_t _len)
{
	int recvCnt = recv(mSocket, static_cast<char*>(_data), _len, 0);
	if (recvCnt < 0)
	{
		SocketUtil::ReportError("TCPSocket::Receive");
		return -SocketUtil::GetLastError();
	}
	return recvCnt;
}

int TCPSocket::Bind(const SocketAddress& _addr)
{
	int err = bind(mSocket, &_addr.mSockAddr, _addr.GetSize());
	if (err != NO_ERROR)
	{
		SocketUtil::ReportError("TCPSocket::Bind");
		return SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

TCPSocket::~TCPSocket()
{
#if _WIN32
	closesocket(mSocket);
#else
	close(mSocket);
#endif // _WIN32

}