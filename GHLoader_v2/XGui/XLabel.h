#pragma once
#include "XControl.h"

#define WS_XLABEL WS_VISIBLE | WS_CHILD | SS_OWNERDRAW

class CXLabel : public CXControl
{
public:
	CXLabel(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXLabel();
	//virtual bool Create();
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	//virtual LRESULT OnCtlColor(WPARAM wParam, LPARAM lParam);

	void SetDrawFlags(DWORD dtFlags);

private:
	DWORD dwFlags;
};

