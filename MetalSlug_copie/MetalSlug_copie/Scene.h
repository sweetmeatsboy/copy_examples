#pragma once

class CScene
{
public:

	explicit CScene(const CRc& rcMain = CRc(), const CPt& ptMain = CPt());
	~CScene();
	CScene(const CScene& rScene);
	CScene& operator=(const CScene& rScene);

	const CRc& getMainRect() const;
	const CPt& getMainPoint() const;

	void setMainRect(CPt::PT_TYPE left, CPt::PT_TYPE up
		, CPt::PT_TYPE right, CPt::PT_TYPE down);
	void setMainRect(const CPt& rPoint1, const CPt& rPoint2);
	void setMainRect(const CRc& rRc);

	void setMainPoint(CPt::PT_TYPE x, CPt::PT_TYPE y);
	void setMainPoint(const CPt& rPoint);

	void pushCollisionRect(const CRc& rRc); // �浿���� �߰�

	const CRc* getCollisionRect(CPt::PT_TYPE x, CPt::PT_TYPE y) const; // �浹���� ���
	const CRc* getCollisionRect(const CPt& rPoint) const; // �浹���� ��� (������ NULL��ȯ)

	const CRc& getCollisionRect(int iIndex) const; /// �ε��� ����

	std::vector<CRc*>::size_type getCountOfCollisionRect() const;

	// ȭ����� �ڽ��� ��ǥ, Ȯ���� ���, Ȯ���� ����� ȭ��� ��ǥ
	bool testCollisionScene(const CPt& ptPos, const CScene& rScene, const CPt& ptPos2) const; // �浹 Ȯ��(2�� �浹�������� Ȯ��)

	void deleteCollisionRect(const CRc& rRc);

	void clearCollisionRect();

public:

	CRc m_rcMain;
	CPt m_ptMain;

	std::vector<CRc*> m_rcCollisions; // �浹 ������
};