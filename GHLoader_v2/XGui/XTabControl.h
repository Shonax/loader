#pragma once
#include "XOwnerDrawControl.h"

#define WS_XTABCONTROL WS_TABSTOP | WS_VISIBLE | WS_CHILD | TCS_OWNERDRAWFIXED

class CXTabControl : public CXOwnerDrawControl
{
public:
	CXTabControl(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXTabControl();

	virtual bool Create();
/*
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCtlColor(WPARAM wParam, LPARAM lParam);*/
	virtual void Draw(HTHEME hTheme, LPDRAWITEMSTRUCT lpDI);

	bool AddTab(tstring szText);

private:
	TCITEM tcItem{ 0 };
	int tabCount = 0;
	std::vector<tstring> szTabs;
};

