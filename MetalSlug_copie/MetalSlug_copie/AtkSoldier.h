#pragma once



class CAtkSoldier : public CSoldier
{
private:
	enum E_ActType
	{
		JUMP,
		STAND,
		SIT
	};
	E_ActType m_ActType;
public:
	static const RTTI m_Rtti;
	CAniDCSet* m_AtkSoldierAni;
private:
	int CurFrame;
	int MaxFrameCount;
	int m_AtkFrame;
	DWORD m_dwAniTimer;
	CSoldier * m_Parent;
public:
	void SetAniName(const TCHAR* _Name);
	void SetParentSoldier(CSoldier* _Parent);
	void FireToPlayer();
public:
	void Progress_AtkSoldier_29();//¼ö·ùÅº
	void Progress_AtkSoldier_30();//¼ö·ùÅº
	void Progress_AtkSoldier_32();//¼ö·ùÅº
	void Progress_AtkSoldier_33();//±¼¸®´Â ÆøÅº
	void Progress_AtkSoldier_34();//Áö·Ú
	void Progress_AtkSoldier_35();//ÆøÁ×
	void Progress_AtkSoldier_36();//ÆøÅº 2 ´øÁö´Â ³ð.
	void Progress_AtkSoldier_38();//¹Ú°ÝÆ÷ ½î´Â ³ð.
	void Progress_AtkSoldier_40();//Ä®ÁúÇÏ´Â ³ð
	void Progress_AtkSoldier_41();//Ä®ÁúÇÏ´Â ³ð
	void Progress_AtkSoldier_42();//Ä®ÁúÇÏ´Â ³ð
	void Progress_AtkSoldier_77();//Á¡ÇÁÇÏ¸é¼­ Ä®ÁúÇÏ´Â ³ð.
	void Progress_AtkSoldier_48();//ÀÏ¹ÝÅº ½ð´À ³ð
public:
	virtual void LineCollision();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	CAtkSoldier() {}
	virtual ~CAtkSoldier() {}
};
