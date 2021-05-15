#include "stdafx.h"

string SocketAddress::ToString() const
{
#if _WIN32
	const sockaddr_in* s = GetAsSocketAddrIn();
	char dest[128];
	InetNtop(s->sin_family, const_cast<in_addr*>(&s->sin_addr)
		, dest, sizeof(dest));
	return StringUtils::Sprint("%s:%d", dest, ntohs(s->sin_port));
#endif // _WIN32

}