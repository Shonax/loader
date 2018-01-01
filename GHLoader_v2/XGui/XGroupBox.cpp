#include "XGroupBox.h"
#include "XControls.h"

CXGroupBox::CXGroupBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXOwnerDrawControl(pOwner, xID, GROUPBOX, x, y, w, h, szText, pFont)
{
	szClass = _T("BUTTON");
	SetStyle(BS_XOWNERDRAW);
	hBgr = GetStockBrush(HOLLOW_BRUSH);	
}

CXGroupBox::~CXGroupBox()
{
}

bool CXGroupBox::Create()
{
	//bool ret = CreateXWindow();
	//if(ret)
	//	mODControls[xID] = this;
	//return ret;
	return CXOwnerDrawControl::Create();
}

void CXGroupBox::SetControlManager(CXControls * pControls)
{
	this->pControls = pControls;
}

//LRESULT CXGroupBox::OnDrawItem(WPARAM wParam, LPARAM lParam)
//{
//	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)lParam;
//	HTHEME hTheme = OpenThemeData(hWnd, WC_BUTTON);
//	Draw(hTheme, lpDI);	
//	return 0;
//}
//
//void CXGroupBox::Paint(LPDRAWITEMSTRUCT lpDI)
//{
//	HDC hdc = lpDI->hDC;
//	if (!hBorderPen)
//	{
//		hBorderPen = CreatePen(PS_SOLID, 1, clBorder);
//		SelectPen(hdc, hBorderPen);
//	}
//
//	TEXTMETRIC tmx;
//	GetTextMetrics(hdc, &tmx);
//	SIZE textSize;
//	tstring str = _T(" ") + szText + _T(" ");
//	GetTextExtentPoint32(hdc, str.c_str(), lstrlen(str.c_str()), &textSize);
//	MoveToEx(hdc, rcRect.left, rcRect.top, NULL);
//	LineTo(hdc, rcRect.left + 10, rcRect.top);
//	MoveToEx(hdc, rcRect.right - textSize.cx + 5, rcRect.top, NULL);
//	LineTo(hdc, rcRect.right, rcRect.top);
//	LineTo(hdc, rcRect.right, rcRect.bottom);
//	LineTo(hdc, rcRect.left, rcRect.bottom);
//	LineTo(hdc, rcRect.left, rcRect.top);
//
//	RECT rcText;
//	rcText.top = rcRect.top - (textSize.cy / 2);
//	rcText.left = rcRect.left + 10;
//	rcText.right = rcText.left + textSize.cx;
//	rcText.bottom = rcText.top + textSize.cy;
//
//	//SetBkMode(hdc, OPAQUE);
//	SetTextColor(hdc, clText);
//	DrawText(hdc, str.c_str(), str.length(), &rcText, DT_LEFT);
//}

void CXGroupBox::AddControl()
{
	pControls->AddRadio(0x666, rcRect.left + 5, rcRect.top + 25, 100, 25, L"Testers");
}
