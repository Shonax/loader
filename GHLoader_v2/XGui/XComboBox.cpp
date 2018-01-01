#include "XComboBox.h"

CXComboBox::CXComboBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, COMBOBOX, x, y, w, h, szText, pFont)
{
	szClass = WC_COMBOBOX;
	SetStyle(WS_XCOMBOBOXDROP);
	
}

CXComboBox::~CXComboBox()
{
}

bool CXComboBox::Create()
{
	bool bRet = CXControl::Create();
	AddString(szText);
	return bRet;
}

void CXComboBox::AddString(tstring szText)
{
	this->szText = szText;
	ComboBox_AddString(hWnd, szText.c_str());
}
