#include "XListBox.h"


CXListBox::CXListBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, BUTTON, x, y, w, h, szText, pFont)
{
	szClass = WC_LISTBOX;
	SetStyle(WS_XLISTBOX);
}

CXListBox::~CXListBox()
{
}

bool CXListBox::Create()
{
	if (!CXControl::Create())
		return false;
	
	AddString(szText);
	return true;
}

void CXListBox::AddString(tstring szText)
{
	ListBox_AddString(hWnd, szText.c_str());
}
