#include "XTabControl.h"


CXTabControl::CXTabControl(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXOwnerDrawControl(pOwner, xID, TABCONTROL, x, y, w, h, szText, pFont)
{
	szClass = WC_TABCONTROL;// _T("BUTTON");
	SetStyle(WS_XTABCONTROL);
	hBgr = GetStockBrush(WHITE_BRUSH);
}

CXTabControl::~CXTabControl()
{
}

bool CXTabControl::Create()
{
	bool bRet = CXControl::Create();
	if (!AddTab(szText))
		return false;

	return true;
}

void CXTabControl::Draw(HTHEME hTheme, LPDRAWITEMSTRUCT lpDI)
{
	static int tabCounter = 0;
	RECT rcBG, rcText;
	HFONT font = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);

	int cb_size = 13;
	GetClientRect(hWnd, &rcBG);

	int tabp = TABP_PANE;
	DWORD dwState = TTILES_NORMAL;

	GetThemeBackgroundContentRect(hTheme, lpDI->hDC, tabp, dwState, &rcBG, &rcText);
	
	rcBG.right = rcBG.left + 25;
	DTBGOPTS dtbgOpts{ 0 };
	dtbgOpts.dwSize = sizeof(dtbgOpts);
	dtbgOpts.dwFlags |= DTBG_VALIDBITS;
	dtbgOpts.rcClip = rcBG;

	SelectBrush(lpDI->hDC, this->hBgr);
	DrawThemeBackgroundEx(hTheme, lpDI->hDC, tabp, dwState, &rcBG, &dtbgOpts);
	
	tabp = TABP_TABITEM;

	TEXTMETRIC tm;
	GetTextMetrics(lpDI->hDC, &tm);
	RECT rcItem = lpDI->rcItem;
	rcText = rcItem;
	rcText.top = rcBG.top + (tm.tmHeight / 4);
	rcText.left = rcText.left + tm.tmAveCharWidth;

	int id = lpDI->itemID;

	DTTOPTS dtOpts{ 0 };
	dtOpts.dwSize = sizeof(dtOpts);
	dtOpts.crText = RGB(255, 0, 0);
	dtOpts.dwFlags |= DTT_TEXTCOLOR;

	std::vector<tstring> str;
	str.resize(szTabs.size());

	int x = 0;
	for (int i = str.size() - 1; i >= 0 ; i--)
	{
		str[x] = szTabs[i];
		x++;
	}
	if ((UINT)id < szTabs.size())
		DrawThemeTextEx(hTheme, lpDI->hDC, tabp, dwState, str[id].c_str(), szText.length(), dwDTFlags, &rcText, &dtOpts);

	//if (id < szTabs.size())
	//{
	//	int p = (szTabs.size() - id);
	//	if (p < szTabs.size())
	//}
	tabCounter++;
	if (tabCounter > tabCount)
		tabCounter = 0;
}

bool CXTabControl::AddTab(tstring szText)
{
	tcItem.pszText = &szText[0];
	tcItem.mask = TCIF_TEXT;
	int tabula = TabCtrl_InsertItem(hWnd, tabCount, &tcItem);
	if (tabula < 0)
		return false;
	tabCount = tabula;
	szTabs.push_back(szText);
	return true;
}
