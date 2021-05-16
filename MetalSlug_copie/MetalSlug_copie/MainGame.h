#pragma once

class CMainGame
{
public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};