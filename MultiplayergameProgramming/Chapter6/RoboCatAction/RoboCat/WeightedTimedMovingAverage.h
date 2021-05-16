#pragma once

class WeightedTimedMovingAverage
{
private:
	float mTimeLastEntryMade;
	float mValue;
	float mDuration;
public:
	WeightedTimedMovingAverage(float _duration = 5.f)
		: mDuration(_duration), mValue(0.f)
	{
		mTimeLastEntryMade -= Timing::sInstance.GetTimef();
	}

	void UpdatePerSecond(float _val)
	{
		float time = Timing::sInstance.GetTimef();
		float timeSinceLastEntry = time - mTimeLastEntryMade;

		float valueOverTime = _val / timeSinceLastEntry;

		float fractionOfDuration = (timeSinceLastEntry / mDuration);
		if (fractionOfDuration > 1.f)
			fractionOfDuration = 1.f;
		
		mValue = mValue * (1.f - fractionOfDuration) + valueOverTime * fractionOfDuration;

		mTimeLastEntryMade = time;
	}

	void Update(float _val)
	{
		float time = Timing::sInstance.GetTimef();
		float timeSinceLastEntry = time - mTimeLastEntryMade;

		float fractionOfDuration = (timeSinceLastEntry / mDuration);
		if (fractionOfDuration > 1.f)
			fractionOfDuration = 1.f;

		mValue = mValue * (1.f - fractionOfDuration) + _val * fractionOfDuration;

		mTimeLastEntryMade = time;
	}

	float GetValue() const
	{
		return mValue;
	}
};