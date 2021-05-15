#include "stdafx.h"

SocketAddressPtr SocketAddressFactory::CreateIPv4FromString(const string& _str)
{
	auto pos = _str.find_last_of(':');
	string host, service;
	if (pos == string::npos)
	{
		host = _str.substr(0, pos);
		service = _str.substr(pos + 1);
	}
	else
	{
		host = _str;
		service = "0";
	}
	addrinfo hint;
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;

	addrinfo* ret;
	int err = getaddrinfo(host.c_str(), service.c_str(), &hint, &ret);
	if (err != NO_ERROR && ret != nullptr)
	{
		SocketUtil::ReportError("");
		return nullptr;
	}
	while (ret->ai_addr == nullptr && ret->ai_next != nullptr)
		ret = ret->ai_next;

	if (ret->ai_addr == nullptr)
		return nullptr;

	auto toRet = make_shared<SocketAddress>(*ret->ai_addr);
	freeaddrinfo(ret);
	return toRet;
}