#pragma once

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil
{
public:
	static bool StaticInit();
	static void CleanUp();

	static void ReportError(const char* _desc);
	static int GetLastError();

	static int Select(const vector<TCPSocketPtr>* _inReadSet,
		vector<TCPSocketPtr>* _outReadSet
		, const vector<TCPSocketPtr>*_inWRiteSet,
		vector<TCPSocketPtr>* outWriteSet
		, const vector<TCPSocketPtr>*_inExceptSet,
		vector<TCPSocketPtr>* _outExceptSet);

	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily _fam);
	static TCPSocketPtr CreateTCPSocket(SocketAddressFamily _fam);
private:

	inline static fd_set* FillSetFromVector(fd_set& _outSet
		, const vector<TCPSocketPtr>* _inSockets, int& _ioNaxNfds);
	inline static void FillVectorFromSet(vector<TCPSocketPtr>* _outSockets
		, const vector<TCPSocketPtr>* _inSockets, const fd_set& _set);
};