#pragma once

class SocketAddress
{
private:
	friend class UDPSocket;
	friend class TCPSocket;

	sockaddr mSockAddr;
private:
	sockaddr_in* GetAsSocketAddrIn()
	{
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
	const sockaddr_in* GetAsSocketAddrIn() const
	{
		return reinterpret_cast<const sockaddr_in*>(&mSockAddr);
	}
#if _WIN32
	uint32_t& GetIP4Ref()
	{
		return *reinterpret_cast<uint32_t*>(&GetAsSocketAddrIn()->sin_addr.S_un.S_addr);
	}

	const uint32_t& GetIP4Ref() const 
	{
		return *reinterpret_cast<const uint32_t*>(&GetAsSocketAddrIn()->sin_addr.S_un.S_addr);
	}
#else
	uint32_t& GetIP4Ref()
	{
		return GetAsSockADdrIn()->sin_addr.s_addr;
	}
	const uint32_t& GetIP4Ref() const
	{
		return GetAsSockAddrIn()->sin_addr.s_addr;
	}
#endif // _WIN32
public:
	SocketAddress(uint32_t _addr, uint16_t _port)
	{
		GetAsSocketAddrIn()->sin_family = AF_INET;
		GetIP4Ref() = htonl(_addr);
		GetAsSocketAddrIn()->sin_port = htons(_port);
	}

	SocketAddress(const sockaddr& _addr)
	{
		memcpy(&mSockAddr, &_addr, sizeof(sockaddr));
	}

	SocketAddress()
	{
		GetAsSocketAddrIn()->sin_family = AF_INET;
		GetIP4Ref() = INADDR_ANY;
		GetAsSocketAddrIn()->sin_port = 0;
	}

	bool operator == (const SocketAddress& _other) const
	{
		if (mSockAddr.sa_family != AF_INET)
			return false;
		if (GetAsSocketAddrIn()->sin_port != _other.GetAsSocketAddrIn()->sin_port)
			return false;
		if (GetIP4Ref() != _other.GetIP4Ref())
			return false;
		return true;
	}

	size_t GetHash() const
	{
		size_t ret = 0;
		ret |= GetIP4Ref();
		ret |= static_cast<uint32_t>(GetAsSocketAddrIn()->sin_port) << 13;
		ret |= mSockAddr.sa_family;
		return ret;
	}

	uint32_t GetSize() const
	{
		return sizeof(sockaddr);
	}

	string ToString() const;
};

typedef shared_ptr<SocketAddress> SocketAddressPtr;

namespace std
{
	template<> 
	struct hash<SocketAddress>
	{
		size_t operator() (const SocketAddress& _addr) const
		{
			return _addr.GetHash();
		}
	};
}