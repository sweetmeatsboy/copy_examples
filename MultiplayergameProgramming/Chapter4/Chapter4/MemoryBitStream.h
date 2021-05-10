#pragma once
class GameObject;

inline uint32_t ConvertToFixed(float _no, float _min, float _precision)
{
	return static_cast<int>((_no - _min) / _precision);
}

inline float ConvertFromFixed(uint32_t _no, float _min, float _precision)
{
	return static_cast<float>(_no) * _precision + _min;
}


class OutputMemoryBitStream
{
private:
	void ReallocBuffer(uint32_t _newCapacity);
	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;
public:
	OutputMemoryBitStream()
		: mBitHead(0), mBuffer(nullptr)
	{
		ReallocBuffer(1500 * 8);
	}

	~OutputMemoryBitStream() { free(mBuffer); }

	void WriteBits(uint8_t _data, uint32_t _bitCnt);
	void WriteBits(const void* _data, uint32_t _bitCnt);

	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetBitLength() const { return mBitHead; }
	uint32_t GetByteLength() const { return (mBitHead + 7) >> 3; }

	void WriteBytes(const void* _data, uint32_t _byteCnt)
	{
		WriteBits(_data, _byteCnt << 3);
	}

	template<typename T>
	void Write(T _data, uint32_t _bitCnt = sizeof(T) * 8)
	{
		static_assert(is_arithmetic<T>::value
			|| is_enum<T>::value, "");
		WriteBits(&_data, _bitCnt);
	}

	void Write(bool _data);
	void Write(const Vector3& _vect);
	void Write(const Quaternion& _q);

	void Write(const string& _str)
	{
		uint32_t eleCnt = static_cast<uint32_t>(_str.size());
		Write(eleCnt);
		for (const auto& ele : _str)
		{
			Write(ele);
		}
	}
};

; class InputMemoryBitStream
{
private :
	char* mBuffer;
	uint32_t mBitHead;
	uint32_t mBitCapacity;
	bool mIsBufferOwner;
public:
	InputMemoryBitStream(char* _buf, uint32_t _bitCnt)
		:mBuffer(_buf),
		mBitCapacity(_bitCnt),
		mBitHead(0),
		mIsBufferOwner(false)
	{}

	InputMemoryBitStream(const InputMemoryBitStream& _other):
		mBuffer(_other.mBuffer)
		, mBitCapacity(_other.mBitCapacity)
		, mBitHead(_other.mBitHead)
		, mIsBufferOwner(true)
	{
		int byteCnt = mBitCapacity / 8;
		mBuffer = static_cast<char*>(malloc(byteCnt));
		memcpy(mBuffer, _other.mBuffer, byteCnt);
	}

	InputMemoryBitStream()
	{
		if (mIsBufferOwner)
			free(mBuffer);
	}

	const char* GetBufferPtr() const
	{
		return mBuffer;
	}

	uint32_t GetRemainingBitCount() const
	{
		return mBitCapacity - mBitHead;
	}

	void ReadBits(uint8_t& _data, uint32_t _bitCnt);
	void ReadBits(void* _data, uint32_t _bitCnt);
	void ReadBytes(void* _data, uint32_t _byteCnt);

	template<typename T>
	void Read(T& _data, uint32_t _bitCnt = sizeof(T) * 8)
	{
		static_assert(is_arithmetic<T>::value
			|| is_enum<T>::value, "");
		ReadBits(&_data, _bitCnt);
	}

	void Read(uint32_t& _data, uint32_t _bitCnt = 32)
	{
		ReadBits(&_data, _bitCnt);
	}
	void Read(int& _data, uint32_t _bitCnt = 32)
	{
		ReadBits(&_data, _bitCnt);
	}
	void Read(float& _data)
	{
		ReadBits(&_data, 32);
	}
	void Read(uint16_t& _data, uint32_t _bitCnt = 16)
	{
		ReadBits(&_data, _bitCnt);
	}
	void Read(int16_t& _data, uint32_t _bitCnt = 16)
	{
		ReadBits(&_data, _bitCnt);
	}
	void Read(uint8_t& _data, uint32_t _bitCnt = 8)
	{
		ReadBits(&_data, _bitCnt);
	}
	void Read(bool& _data)
	{
		ReadBits(&_data, 1);
	}

	void Read(Quaternion& _q);
	void ResetToCapacity(uint32_t _byteCnt)
	{
		mBitCapacity = _byteCnt << 3; 
		mBitHead = 0;
	}


	void Read(string& _str)
	{
		uint32_t eleCnt;
		Read(eleCnt);
		_str.resize(eleCnt);
		for (auto& ele : _str)
			Read(ele);
	}

	void Read(Vector3& _vec);
};