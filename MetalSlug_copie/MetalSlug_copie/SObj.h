#pragma once

class CSObj
{
protected:
public:
	virtual void Initialize() = 0;
	virtual void Progress() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
public:
	CSObj() {}
	virtual ~CSObj() {}
};