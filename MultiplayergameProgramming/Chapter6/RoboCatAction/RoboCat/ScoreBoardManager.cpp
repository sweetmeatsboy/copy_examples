#include "stdafx.h"

std::unique_ptr<ScoreBoardManager> ScoreBoardManager::sInstance;

void ScoreBoardManager::Staticinit()
{
	sInstance.reset(new ScoreBoardManager());
}

ScoreBoardManager::ScoreBoardManager()
{
	mDefaultColors.push_back(Colors::LightYellow);
	mDefaultColors.push_back(Colors::LightBlue);
	mDefaultColors.push_back(Colors::LightPink);
	mDefaultColors.push_back(Colors::LightGreen);
}

ScoreBoardManager::Entry::Entry(uint32_t _pid, const string& _pName, const Vector3& _color)
	:mPlayerId(_pid)
	, mPlayerName(_pName)
	, mColor(_color)
{
	SetScore(0);
}

void ScoreBoardManager::Entry::SetScore(int32_t _score)
{
	mScore = _score;

	char buf[256];
	snprintf(buf, 256, "%s %i", mPlayerName.c_str(), mScore);
	mFormattedNameScore = string(buf);
}

ScoreBoardManager::Entry* ScoreBoardManager::GetEntry(uint32_t _pid)
{
	for (auto& ele : mEntries)
	{
		if (ele.GetPlayerId() == _pid)
			return &ele;
	}
	return nullptr;
}

bool ScoreBoardManager::RemoveEntry(uint32_t _pid)
{
	for (auto iter = mEntries.begin(), endit = mEntries.end();
		iter != endit; iter++)
	{
		if ((*iter).GetPlayerId() == _pid)
		{
			mEntries.erase(iter);
			return true;
		}
	}

	return false;
}

void ScoreBoardManager::AddEntry(uint32_t _pid, const string& _pName)
{
	RemoveEntry(_pid);
	mEntries.emplace_back(_pid, _pName, mDefaultColors[_pid % mDefaultColors.size()]);

}

void ScoreBoardManager::incScore(uint32_t _pid, int _amount)
{
	Entry* p = GetEntry();
	if (p == nullptr)
		return;
	p->SetScore(p->GetScore() + _amount);
}

bool ScoreBoardManager::Write(OutputMemoryBitStream& _in) const
{
	int cnt = mEntries.size();
	for (const Entry& ele : mEntries)
	{
		ele.Write(_in);
	}
	return true;
}

bool ScoreBoardManager::Read(InputMemoryBitStream& _in)
{
	int cnt;
	_in.Read(cnt);
	mEntries.reserve(cnt);
	for (Entry& ele : mEntries)
	{
		ele.Read(_in);
	}
	return true;
}

bool ScoreBoardManager::Entry::Write(OutputMemoryBitStream& _in) const
{
	bool didSucced = true;
	_in.Write(mColor);
	_in.Write(mPlayerId);
	_in.Write(mPlayerName);
	_in.Write(mScore);
	return didSucced;
}

bool ScoreBoardManager::Entry::Read(InputMemoryBitStream& _in)
{
	bool didSucceed = true;
	_in.Read(mColor);
	_in.Read(mPlayerId);
	_in.Read(mPlayerName);

	int score;
	_in.Read(score);
	if (didSucceed)
		SetScore(score);
	return didSucceed;
}