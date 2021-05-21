#pragma once
class ScoreBoardManager
{
public:
	static void Staticinit();
	static std::unique_ptr<ScoreBoardManager> sInstance;
public:
	class Entry
	{
	private:
		Vector3 mColor;
		uint32_t mPlayerId;
		string mPlayerName;
		int mScore;
		string mFormattedNameScore;
	public:
		Entry() {};
		Entry(uint32_t _pid, const string& _pName, const Vector3& _color);
	public:
		const Vector3& GetColor() const { return mColor; }
		uint32_t GetPlayerId() const { return mPlayerId; }
		const string& GetPlayerName() const { return mPlayerName; }
		const string& GetFormattedNameScore() const
		{
			return mFormattedNameScore;
		}
		int GetScore() const { return mScore; }
		void SetScore(int _score);
		bool Write(OutputMemoryBitStream& _in) const;
		bool Read(InputMemoryBitStream& _in);
	public:
		static uint32_t GetSerializedSize();
	};
public:
	Entry* GetEntry(uint32_t _pid);
	bool RemoveEntry(uint32_t _pid);
	void AddEntry(uint32_t _pid, const string& _pName);
	void incScore(uint32_t _pid, int _incAmount);

	bool Write(OutputMemoryBitStream& _in) const;
	bool Read(InputMemoryBitStream& _in);

	const vector<Entry>& GetEntries()const { return mEntries; }

private:
	ScoreBoardManager();

	vector<Entry>mEntries;
	vector<Vector3> mDefaultColors;
};

