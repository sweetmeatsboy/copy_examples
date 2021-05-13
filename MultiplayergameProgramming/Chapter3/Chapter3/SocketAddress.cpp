#include "pch.h"

string SocketAddress::ToString() const
{
#if _WIN32
	const sockaddr_in* s = GetAsSockAddrIn();
	char dest[128];
	InetNtop(s->sin_family, const_cast<in_addr*>(&s->sin_addr)
		, dest, sizeof(dest));
	return StringUtils::Sprintf("%s:%d", dest, ntohs(s->sin_port));
#else
#endif
}
