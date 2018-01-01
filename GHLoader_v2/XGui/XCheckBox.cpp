#include "XCheckBox.h"

CXCheckBox::CXCheckBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXOwnerDrawControl(pOwner, xID, CHECKBOX, x, y, w, h, szText, pFont)
{
	szClass = _T("BUTTON");
	SetStyle(BS_XOWNERDRAW);
	hBgr = GetStockBrush(HOLLOW_BRUSH);
}

CXCheckBox::~CXCheckBox()
{
}
