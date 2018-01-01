#include "XRichText.h"



CXRichText::CXRichText(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, BUTTON, x, y, w, h, szText, pFont)
{
	szClass = MSFTEDIT_CLASS;
	SetStyle(WS_XRICHTEXT);
}


CXRichText::~CXRichText()
{
}

void CXRichText::SetBgColor(COLORREF color)
{
	SendMessage(hWnd, EM_SETBKGNDCOLOR, 0, (LPARAM)color);
}

void CXRichText::SetTxtColor(COLORREF color)
{
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(cf));
	cf.cbSize = sizeof(CHARFORMAT2);
	DWORD dwMask = SendMessage(hWnd, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cf);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0;
	cf.crTextColor = color;
	SendMessage(hWnd, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
}
