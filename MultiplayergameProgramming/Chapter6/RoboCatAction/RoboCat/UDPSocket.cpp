#include "stdafx.h"

int UDPSocket::Bind(const SocketAddress& _addr)
{
	int err = bind(mSocket, &_addr.mSockAddr, _addr.GetSize());
	if (err != 0)
	{
		SocketUtil::ReportError("");
		return SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int UDPSocket::SendTo(const void* _data, int _len, const SocketAddress& _addr)
{
	int sentCnt = sendto(mSocket, static_cast<const char*>(_data)
		, _len, 0, &_addr.mSockAddr, _addr.GetSize());
	if (sentCnt <= 0)
	{
		SocketUtil::ReportError("UDPSocket::SendTo");
		return -SocketUtil::GetLastError();
	}
	return sentCnt;
}

int  UDPSocket::ReceiveFrom(void* _data, int _len, SocketAddress& _addr)
{
	socklen_t slen = _addr.GetSize();
	int recvCnt = recvfrom(mSocket, static_cast<char*>(_data), _len, 0, &_addr.mSockAddr, &slen);
	if (recvCnt >= 0)
	{
		return recvCnt;
	}
	else
	{
		int err = SocketUtil::GetLastError();
		if (err == WSAEWOULDBLOCK)
		{
			return 0;
		}
		else if (err == WSAECONNRESET)
		{
			return -WSAECONNRESET;
		}
		else
		{
			return -err;
		}
	}
}

UDPSocket::~UDPSocket()
{
#if _WIN32
	closesocket(mSocket);
#else
	close(mSocket)
#endif // _WIN32
}

int UDPSocket::SetNonBlockingMode(bool _flag)
{
#if _WIN32
	u_long arg = _flag ? 1 : 0;
	int ret = ioctlsocket(mSocket, FIONBIO, &arg);
#else
	int flags = fcntl(mSocket, F_GETFL, 0);
	flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
	int result = fcntl(mSocket, F_SETFL, flags);
#endif // _WIN32

	if (ret == SOCKET_ERROR)
	{
		SocketUtil::ReportError("UDPSocket::SetNonBlockingMode");
		return SocketUtil::GetLastError();
	}
	else
	{
		return NO_ERROR;
	}
}