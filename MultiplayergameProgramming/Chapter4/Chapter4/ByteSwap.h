#pragma once

inline uint16_t ByteSwap2(uint16_t _data)
{
	return (_data >> 8) | (_data << 8);
}

inline uint32_t ByteSwap4(uint32_t _data)
{
	return ((_data >> 24) & 0x000000ff)
		| ((_data >> 8) & 0x0000ff00)
		| ((_data << 8) & 0x00ff0000)
		| ((_data << 24) & 0xff000000);
}

inline uint64_t ByteSwap8(uint64_t inData)
{
	return  ((inData >> 56) & 0x00000000000000ff) |
		((inData >> 40) & 0x000000000000ff00) |
		((inData >> 24) & 0x0000000000ff0000) |
		((inData >> 8) & 0x00000000ff000000) |
		((inData << 8) & 0x000000ff00000000) |
		((inData << 24) & 0x0000ff0000000000) |
		((inData << 40) & 0x00ff000000000000) |
		((inData << 56) & 0xff00000000000000);
}


template <typename tFrom, typename tTo>
class TypeAliaser
{
public:
	union
	{
		tFrom mAsFromType;
		tTo mAsToType;
	};

	TypeAliaser(tFrom _from)
		:mAsFromType(_from)
	{
	}
	tTo& Get() { return mAsToType; }
};


template <typename T, size_t tsize>
class ByteSwapper;

template<typename T>
class ByteSwapper<T, 1>
{
public :
	T Swap(T _data) const
	{
		return _data;
	}
};

template <typename T>
class ByteSwapper<T, 2>
{
public:
	T Swap(T _data) const
	{
		uint16_t ret = ByteSwap2(TypeAliaser<T, uint16_t>(_data).Get());
		return TypeAliaser<uint16_t, T>(ret).Get();
	}
};


template <typename T>
class ByteSwapper<T, 4>
{
public:
	T Swap(T _data) const
	{
		uint32_t ret = ByteSwap4(TypeAliaser<T, uint32_t>(_data).Get());
		return TypeAliaser<uint32_t, T>(ret).Get();
	}
};


template <typename T>
class ByteSwapper<T, 8>
{
public:
	T Swap(T _data) const
	{
		uint64_t ret = ByteSwap(TypeAliaser<T, uint64_t>(_data).Get());
		return TypeAliaser<uint64_t, T>(ret).Get();
	}
};