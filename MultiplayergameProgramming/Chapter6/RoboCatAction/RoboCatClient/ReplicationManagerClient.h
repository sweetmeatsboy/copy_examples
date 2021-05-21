#pragma once
class ReplicationManagerClient
{
private:
	void ReadAndDoCreateAction(InputMemoryBitStream& _in, int _nid);
	void ReadAndDoUpdateAction(InputMemoryBitStream& _in, int _nid);
	void ReadAndDoDestroyAction(InputMemoryBitStream& _in, int _nid);
public:
	void Read(InputMemoryBitStream& _in);
};

