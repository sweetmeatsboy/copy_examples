#pragma once

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6,
};

class SocketUtil
{
private:
	inline static fd_set* FillSetFromVector(fd_set& _outSet
		, const vector<TCPSocketPtr>* _inSockets, int& _ioNaxNfdxs);
	inline static void FillVectorFromSet(vector<TCPSocketPtr>* _outSockets
		, const vector<TCPSocketPtr>* _inSockets, const fd_set& _inSet);
public:

	static bool StaticInit();
	static void CleanUp();

	static void ReportError(const char* _desc);
	static int GetLastError();

	static int Select(const vector<TCPSocketPtr>* _inRead
		, vector<TCPSocketPtr>* _outRead
		, const vector<TCPSocketPtr>* _inWrite
		, vector<TCPSocketPtr>* _outWrite
		, const vector<TCPSocketPtr>* _inExcept
		, vector<TCPSocketPtr>* _outExcept);

	static TCPSocketPtr CreateTCPSocket(SocketAddressFamily _af);
	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily _af);

};