#include "pch.h"

bool SocketUtil::StaticInit()
{
#if _WIN32
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != NO_ERROR)
	{
		ReportError("StartUp failed");
		return false;
	}
#endif
	return true;
}

void SocketUtil::CleanUp()
{
#if _WIN32
	WSACleanup();
#endif
}

void SocketUtil::ReportError(const char* _desc)
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


	LOG("Error %s: %d- %s", _desc, errorNum, lpMsgBuf);
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
	if (s != INVALID_SOCKET)
	{
		return UDPSocketPtr(new UDPSocket(s));
	}
	ReportError("CreateUDPSocket");
	return nullptr;
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily _af)
{
	SOCKET s = socket(_af, SOCK_STREAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET)
	{
		return TCPSocketPtr(new TCPSocket(s));
	}
	ReportError("CreateTcpSocket");
	return nullptr;
}

fd_set* SocketUtil::FillSetFromVector(fd_set& _outSet, const  vector<TCPSocketPtr>* _inSockets, int& _ioNaxfds)
{
	if (_inSockets == nullptr)
		return nullptr;

	FD_ZERO(&_outSet);
	for (const TCPSocketPtr& _s : *_inSockets)
	{
		FD_SET(_s->mSocket, &_outSet);
#if !_WIN32
		_ioNaxfds = std::max(_ioNaxfds, socket->mSocket);
#endif
	}
	return &_outSet;
}

void SocketUtil::FillVectorFromSet(vector<TCPSocketPtr>* _outSockets, const vector<TCPSocketPtr>* _inSockets, const fd_set& _inSet)
{
	if (_inSockets == nullptr)
		return;
	if (_outSockets == nullptr)
		return;
	_outSockets->clear();
	for (const TCPSocketPtr& _s : *_inSockets)
	{
		if (FD_ISSET(_s->mSocket, &_inSet))
		{
			_outSockets->push_back(_s);
		}
	}
}


int SocketUtil::Select(const vector<TCPSocketPtr> * _inReadSet,
	vector<TCPSocketPtr>* _outReadSet,
	const vector<TCPSocketPtr> * _inWriteSet,
	vector<TCPSocketPtr>* _outWriteSet,
	const vector<TCPSocketPtr> * _inExceptSet,
	vector<TCPSocketPtr>* _outExcpetSet)
{
	int ret = 0;

	fd_set read, write, except;

	int nfds = 0;

	fd_set* readPtr = FillSetFromVector(read, _inReadSet, nfds);
	fd_set* writePtr = FillSetFromVector(write, _inWriteSet, nfds);
	fd_set* exceptPtr = FillSetFromVector(except, _inExceptSet, nfds);

	int toRet = select(nfds + 1, readPtr, writePtr, exceptPtr, nullptr);
	if (toRet > 0)
	{
		FillVectorFromSet(_outReadSet, _inReadSet, read);
		FillVectorFromSet(_outWriteSet, _inWriteSet, write);
		FillVectorFromSet(_outExcpetSet, _inExceptSet, except);
	}

	return ret;
}