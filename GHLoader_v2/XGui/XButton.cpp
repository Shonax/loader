#include "XButton.h"

CXButton::CXButton(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, BUTTON, x, y, w, h, szText, pFont)
{
	szClass = _T("BUTTON");
	SetStyle(BS_XBUTTONICON);
}


CXButton::~CXButton()
{
}

bool CXButton::Create()
{
	if (!CreateXWindow())
		return false;
	if (pFont)
		SetFont(pFont);
	return true;
}

void CXButton::SetCommandArgs(uintptr_t pArgs)
{
	this->pCommandArgs = pArgs;
}

int CXButton::OnCommand(WPARAM wParam, LPARAM lParam, uintptr_t pArg1)
{	
	if (fnAction)
	{
		if (HIWORD(wParam) == BN_CLICKED)
		{
			fnAction(pArg1);
		}
	}
	return 0;
}

int CXButton::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		if(fnAction)
			fnAction(pCommandArgs);
	}
	return 0;
}

int CXButton::SetIcon(HICON hIcon)
{
	this->hIcon = hIcon;
	SetStyle(BS_XBUTTONICON);
	//dwStyle |= BS_BITMAP;
	SendMessage(hWnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	//RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
	return 0;
}

