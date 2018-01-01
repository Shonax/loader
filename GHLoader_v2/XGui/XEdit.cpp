#include "XEdit.h"

CXEdit::CXEdit(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, EDIT, x, y, w, h, szText, pFont)
{
	szClass = _T("EDIT");
	SetStyle(WS_XEDITML);
	this->bMultiLine = true;
}

CXEdit::~CXEdit()
{
}

bool CXEdit::Create()
{
	if (!bMultiLine && GetHeight() == 0)
	{
		TEXTMETRIC tm;
		GetTextMetrics(GetDC(hWnd), &tm);
		this->SetHeight(tm.tmHeight + 2);
	}
	if (!CreateXWindow())
		return false;

	if (pFont)
		SetFont(pFont);
	
	return true;
}

tstring CXEdit::GetText()
{
	szText.clear();
	szText.resize(Edit_GetTextLength(hWnd) + 1);
	Edit_GetText(hWnd, &szText[0], szText.size());
	return szText;
}
