#pragma once
#include "XControl.h"

#define WS_XLISTBOX WS_VISIBLE | WS_CHILD | WS_VSCROLL| LBS_EXTENDEDSEL

class CXListBox : public CXControl
{
public:
	CXListBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXListBox();

	virtual bool Create();
	void AddString(tstring szText);
};

