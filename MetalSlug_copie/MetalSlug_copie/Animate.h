#pragma once


class CAnimate
{
public:
	struct tagScene
	{
		DWORD m_dwIndex;
		DWORD m_dwOutputTime;
	};
private:
	vector<tagScene*> m_vScenes;
public:
	CAnimate();
	CAnimate(const CAnimate& _other);
	~CAnimate();
	CAnimate& operator=(const CAnimate& _other);

	bool addScene(DWORD _idx, DWORD _time = 100);
	bool deleteScene(DWORD _idx);

	vector<tagScene*>::size_type getCntScene() const;
	const tagScene* getIdxOfScene(int _idx) const;
	bool changeTime(DWORD _idx, DWORD _time);

	void downIdx(DWORD _idx);

	void clearScenes();
};