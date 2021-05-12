#pragma once

#include <cstdlib>
#include <cstdint>
#include <type_traits>

#define STREAM_ENDIANNESS 0;
#define PLATFORM_ENDIANESS 0;

class GameObject;
class LinkingContext;

class OutputMemoryStream
{
public:
	OutputMemoryStream()
		: mLinkingContext(nullptr)
	{
		ReallocBuffer(32);
	}
	~OutputMemoryStream()
	{
		free(mBuffer);
	}

	const char* GetBuffer() const {
		return mBuffer;
	}
	uint32_t GetLength() const {
		return mHead;
	}
	void		Write(const void* inData,
		size_t inByteCount);

	template<typename T>
	void Write(T _data)
	{
		static_assert(std::is_arithmetic<T>::vaie
			|| std::is_enum<T>::value,
			"");

		if (STREAM_ENDIANNESS == PLATFORM_ENDIANESS)
		{
			Write(&_data, sizeof(_data));
		}
		else
		{
			T swappedData = ByteSwap(_data);
			Write(&swappedData, sizeof(swappedData));
		}
	}

	void Write(const std::vector< int >& _inIntVector)
	{
		size_t eleCnt = _inIntVector;
		Write(eleCnt);
		Write(_inIntVector.data(), eleCnt* sizeof(int));
	}

	template<typename T>
	void Write(const std::vector<T>& _vector)
	{
		uint32_t eleCnt = _vector;
		Write(eleCnt);
		for (const T& _ele : _vector)
			Write(_ele);
	}

	void Write(const GameObject* _obj)
	{
		uint32_t networkId = mLinkingContext->GetNetworkId(const_cast<GameObject*>(_obj), false);		
		Write(networkId);
	}
private :
	void ReallocBuffer(uint32_t _newLen);
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;

	LinkingContext* mLinkingContext;
};

class InputMemoryStream
{
public:
	InputMemoryStream(char* _buf, uint32_t _byteCnt)
		: mBuffer(_buf), mCapacity(_byteCnt), mHead(0),
		mLinkingContext(nullptr)
	{
	}

	~InputMemoryStream()
	{
		free(mBuffer);
	}

	uint32_t GetRemainDataSize() const
	{
		return mCapacity - mHead;
	}
	void Read(void* _data, uint32_t _byteCnt);

	template <typename T>
	void Read(T& _data)
	{
		static_assert(is_arithmetic<T>::value ||
			is_enum<T>::value, "");
		Read(&_data, sizeof(_data));
	}

	template<typename T>
	void Read(vector<T>& _vect)
	{
		size_t eleCnt;
		Read(eleCnt);
		_vect.resize(eleCnt);
		for (const T& ele : _vect)
			Read(ele);
	}

	void Read(GameObject*& _obj)
	{
		uint32_t nId;
		Read(nId);
		_obj = mLinkingContext->GetGameObject(nId);
	}

private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;

	LinkingContext* mLinkingContext;
};