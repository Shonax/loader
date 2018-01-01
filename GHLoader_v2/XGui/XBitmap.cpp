#include "XBitmap.h"

CXBitmap::CXBitmap(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, IMAGE, x, y, w, h, szText, nullptr)
{
	SetStyle(WS_CHILD | WS_VISIBLE | SS_OWNERDRAW);
	SetClass(_T("STATIC"));
}

CXBitmap::~CXBitmap()
{
}

bool CXBitmap::Load(HBITMAP hBitmap)
{
	bool bRet = true;
	if (!hWnd)
		bRet = Create();
	this->hBitmap = hBitmap;
	RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	return bRet;
}

bool DrawBitmap(HWND hWnd, HDC hdcDest, HBITMAP hBitmap, RECT & pRect)
{
	HDC hdcMemDC = NULL;
	HGDIOBJ bmpObj;
	BITMAP bmp;

	hdcMemDC = CreateCompatibleDC(hdcDest);

	bmpObj = SelectObject(hdcMemDC, hBitmap);
	GetObject(hBitmap, sizeof(BITMAP), &bmp);

	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	SetStretchBltMode(hdcMemDC, HALFTONE);
	SetStretchBltMode(hdcDest, HALFTONE);
	
	if (!StretchBlt(hdcDest,
		pRect.left, pRect.top,
		pRect.right - pRect.left,
		pRect.bottom - pRect.top,
		hdcMemDC, 0, 0,
		bmp.bmWidth, bmp.bmHeight, SRCCOPY))
		return false;

	//BitBlt(hdcDest, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hdcMemDC, 0, 0, SRCCOPY);

	DeleteObject(bmpObj);
	DeleteDC(hdcMemDC);
	return true;
}

LRESULT CXBitmap::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	DRAWITEMSTRUCT* pDi = (DRAWITEMSTRUCT*)lParam;
	DrawBitmap(hWnd, pDi->hDC, hBitmap, GetRect());
	return LRESULT(1);
}
