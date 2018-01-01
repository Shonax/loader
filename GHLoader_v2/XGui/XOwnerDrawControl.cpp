#include "XOwnerDrawControl.h"

std::map<int, CXOwnerDrawControl*> mODControls;

LRESULT CALLBACK OwnerDrawProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	int id = GetDlgCtrlID(hWnd);
	CXOwnerDrawControl* pODControl = mODControls[id];
	
	switch (uMsg)
	{
		case WM_MOUSEMOVE:
		{
			if (pODControl->GetControlType() == GROUPBOX)
				break;
			TRACKMOUSEEVENT tme{ 0 };
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);
			pODControl->SetHot(true);
			InvalidateRect(hWnd, &pODControl->GetRect(), FALSE);
			return 0;
		}
		case WM_MOUSELEAVE:
		{
			if (pODControl->GetControlType() == GROUPBOX)
				break;
			pODControl->SetHot(false);
			InvalidateRect(hWnd, &pODControl->GetRect(), FALSE);
			return 0;
		}
		case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)lParam;
			return mODControls[lpDI->CtlID]->OnDrawItem(wParam, lParam);
			break;
		}
		case WM_CTLCOLOR:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORSTATIC:
		{
			return LRESULT(GetStockObject(HOLLOW_BRUSH));
		}
		case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			mODControls[id]->OnCommand(wParam, lParam);
			return 0;
		}
		case WM_ERASEBKGND:
		{
			return 0;
		}
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

CXOwnerDrawControl::CXOwnerDrawControl(CXWindow * pOwner, XID xID, ECXControl ControlType, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, ControlType, x, y, w, h, szText, pFont)
{
}

CXOwnerDrawControl::~CXOwnerDrawControl()
{
}


bool CXOwnerDrawControl::Create()
{
	mODControls[xID] = this;
	bool ret = CreateXWindow();
	if (ret)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)this);
		SetWindowSubclass(hWnd, OwnerDrawProc, 0, 0);
	}
	return ret;
}

int CXOwnerDrawControl::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		bChecked = !bChecked;
	}

	return 0;
}

void CXOwnerDrawControl::SetText(tstring szText)
{
	this->szText = szText;
	SetWindowText(hWnd, szText.c_str());
}

LRESULT CXOwnerDrawControl::OnDrawItem(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)lParam;
	HTHEME hTheme = OpenThemeData(hWnd, WC_BUTTON);
	Draw(hTheme, lpDI);
	return 0;
}

LRESULT CXOwnerDrawControl::OnCtlColor(WPARAM wParam, LPARAM lParam)
{
	return LRESULT(hBgr);
}

void CXOwnerDrawControl::RedrawCheck()
{
	RECT rc = rcRect;
	rc.right = rc.left + 25;
	InvalidateRect(hWnd, &rc, FALSE);
}

void CXOwnerDrawControl::SetCheck(bool bCheck)
{
	this->bChecked = bCheck;
	RedrawCheck();
}

bool CXOwnerDrawControl::GetCheck()
{
	return bChecked;
}

void CXOwnerDrawControl::ToggleCheck()
{
	bChecked = !bChecked;
	RedrawCheck();
}

void CXOwnerDrawControl::SetHot(bool isHot)
{
	this->bHot = isHot;
}

//for radios and checkboxes

void CXOwnerDrawControl::DetermineTypeAndState(int & iButtonPart, DWORD & dwState)
{
	switch (ControlType)
	{
		case RADIO:
			iButtonPart = BP_RADIOBUTTON;
			if (bChecked)
			{
				dwState = RBS_CHECKEDNORMAL;
			}
			else
			{
				dwState = RBS_UNCHECKEDNORMAL;
			}
			if (bHot)
				dwState |= RBS_HOT;
			break;

		case CHECKBOX:
			iButtonPart = BP_CHECKBOX;
			if (bChecked)
			{
				dwState = CBS_CHECKEDNORMAL;
			}
			else
			{
				dwState = CBS_UNCHECKEDNORMAL;
			}
			if (bHot)
				dwState |= CBS_HOT;
			break;

		case GROUPBOX:
			iButtonPart = BP_GROUPBOX;
			dwState = GBS_NORMAL;
			break;
	}
}

void CXOwnerDrawControl::Draw(HTHEME hTheme, LPDRAWITEMSTRUCT lpDI)
{
	RECT rcBG, rcText;
	HFONT font = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);

	int cb_size = 13;
	GetClientRect(hWnd, &rcBG);

	int bp;
	DWORD rbState;	
	DetermineTypeAndState(bp, rbState);

	TEXTMETRIC tm;
	GetTextMetrics(lpDI->hDC, &tm);

	GetThemeBackgroundContentRect(hTheme, lpDI->hDC, bp, rbState, &rcBG, &rcText);
	if (ControlType == GROUPBOX)
	{
		rcBG.top += tm.tmHeight / 2; // line the top line with the center of the text
		SIZE szSize{ 0 };
		GetTextExtentPoint32(lpDI->hDC, szText.c_str(), szText.length(), &szSize);

		RECT rcItem = lpDI->rcItem;
		rcText = rcItem;
		rcText.bottom = rcBG.top + tm.tmHeight;
		rcText.left = rcText.left + cb_size;
		rcText.right = rcText.left + szSize.cx + 8;
	}
	else
	{
		rcBG.right = rcBG.left + 25;
		rcText.top = rcBG.top + (tm.tmHeight / 4);
		rcText.left = rcText.left + 25;
	}

	DTBGOPTS dtbgOpts{ 0 };
	dtbgOpts.dwSize = sizeof(dtbgOpts);
	dtbgOpts.dwFlags |= DTBG_VALIDBITS;
	dtbgOpts.rcClip = rcBG;

	SelectBrush(lpDI->hDC, GetStockObject(HOLLOW_BRUSH));
	DrawThemeBackgroundEx(hTheme, lpDI->hDC, bp, rbState, &rcBG, &dtbgOpts);
	GetThemeBackgroundContentRect(hTheme, lpDI->hDC, bp, rbState, &rcBG, &rcRect);
	if (ControlType == GROUPBOX)
	{
		COLORREF clBgr = GetOwnerWindow()->GetBackgroundColor();
		hBgr = CreateSolidBrush(clBgr);
		FillRect(lpDI->hDC, &rcText, hBgr);
		rcText.left += 4;
	}

	DTTOPTS dtOpts{ 0 };
	dtOpts.dwSize = sizeof(dtOpts);
	dtOpts.crText = RGB(255, 0, 0);
	dtOpts.dwFlags |= DTT_TEXTCOLOR;
	DrawThemeTextEx(hTheme, lpDI->hDC, bp, rbState, szText.c_str(), szText.length(), dwDTFlags, &rcText, &dtOpts);
}