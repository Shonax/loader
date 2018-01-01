#include "XTrackBar.h"

#define WS_XTRACKBAR WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE

CXTrackBar::CXTrackBar(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, TRACKBAR, x, y, w, h, szText, pFont)
{
	szClass = TRACKBAR_CLASS;
	SetStyle(WS_XTRACKBAR);
}


CXTrackBar::~CXTrackBar()
{
}

bool CXTrackBar::Create()
{
	bool bRet = CXControl::Create();
	SendMessage(hWnd, TBM_SETRANGE, TRUE, MAKELONG(iMin, iMax));
	SendMessage(hWnd, TBM_SETPOS, TRUE, iSelMin);
	return bRet;
}

LRESULT CXTrackBar::OnCtlColor(WPARAM wParam, LPARAM lParam)
{
	if (!hBgr)
		hBgr = CreateSolidBrush(pOwnerWindow->GetBackgroundColor());
	return (LRESULT)hBgr;
}
