#include "stdafx.h"

bool SocketUtil::StaticInit()
{
#if _WIN32
	WSAData wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != NO_ERROR)
	{
		ReportError("Startup err");
		return false;
	}
#endif // _WIN32
	return true;
}

void SocketUtil::CleanUp()
{
#if _WIN32
	WSACleanup();
#endif // _WIN32
}


void SocketUtil::ReportError(const char* inOperationDesc)
{
#if _WIN32
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);


	LOG("Error %s: %d- %s", inOperationDesc, errorNum, lpMsgBuf);
#else
	LOG("Error: %hs", inOperationDesc);
#endif
}

int SocketUtil::GetLastError()
{
#if _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif

}

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily _af)
{
	SOCKET s = socket(_af, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
	{
		ReportError("SocketUtil::CreateUDPSocket");
		return nullptr;
	}
	return UDPSocketPtr(new UDPSocket(s));
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily _af)
{
	SOCKET s = socket(_af, SOCK_DGRAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(s));
	ReportError("SocketUtil::CreateTCPSocket");
	return nullptr;
}

fd_set* SocketUtil::FillSetFromVector(fd_set& _outSet, const vector<TCPSocketPtr>* _sockets, int& _ioNaxNfds)
{
	if (_sockets == nullptr)
		return;
	FD_ZERO(&_outSet);
	for (const auto& ele : *_sockets)
	{
		FD_SET(ele->mSocket, &_outSet);
#if !_WIN32
		_ioNaxNfds = max(_ioNaxNfds, ele->mSocket);
#endif // _WIN32
	}
	return &_outSet;
}

void SocketUtil::FillVectorFromSet(vector<TCPSocketPtr>* _out, const vector<TCPSocketPtr>* _in, const fd_set& _inSet)
{
	if (_in == nullptr || _out == nullptr)
		return;
	_out->clear();
	for (const auto &ele : *_in)
	{
		if (FD_ISSET(ele->mSocket, &_in))
			_out->push_back(ele);
	}
}

int SocketUtil::Select(const vector< TCPSocketPtr >* inReadSet,
	vector< TCPSocketPtr >* outReadSet,
	const vector< TCPSocketPtr >* inWriteSet,
	vector< TCPSocketPtr >* outWriteSet,
	const vector< TCPSocketPtr >* inExceptSet,
	vector< TCPSocketPtr >* outExceptSet)
{
	fd_set read, write, except;

	int nfds = 0;

	fd_set* readPtr = FillSetFromVector(read, inReadSet, nfds);
	fd_set* writePtr = FillSetFromVector(write, inWriteSet, nfds);
	fd_set* exceptPtr = FillSetFromVector(except, inExceptSet, nfds);

	int ret = select(nfds + 1, readPtr, writePtr, exceptPtr, nullptr);

	if (ret > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return ret;
}