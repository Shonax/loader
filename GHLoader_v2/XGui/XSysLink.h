#pragma once
#include "XControl.h"
class CXSysLink : public CXControl
{
public:
	CXSysLink(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXSysLink();

	virtual bool Create();
	virtual void OnNotify(UINT code, LPARAM lParam);
};

