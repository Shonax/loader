#include "XRadioButton.h"
#include "XControls.h"

std::map<int, CXRadioButton*> mRadios;

LRESULT CALLBACK RadioProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	int id = GetDlgCtrlID(hWnd);
	CXRadioButton* pRadio = mRadios[id];
	switch (uMsg)
	{
		case WM_MOUSEMOVE:
		{
			TRACKMOUSEEVENT tme{ 0 };
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);
			pRadio->SetHot(true);
			InvalidateRect(hWnd, &pRadio->GetRect(), FALSE);
			return 0;
		}
		case WM_MOUSELEAVE:
		{
			pRadio->SetHot(false);
			InvalidateRect(hWnd, &pRadio->GetRect(), FALSE);
			return 0;
		}
		case WM_ERASEBKGND:
		{
			return 0;
		}
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

CXRadioButton::CXRadioButton(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXOwnerDrawControl(pOwner, xID, RADIO, x, y, w, h, szText, pFont)
{
	szClass = _T("BUTTON");
	SetStyle(BS_XOWNERDRAW);
	hBgr = GetStockBrush(HOLLOW_BRUSH);
}

CXRadioButton::~CXRadioButton()
{
}

bool CXRadioButton::Create()
{	
	return CXOwnerDrawControl::Create();
}

int CXRadioButton::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		if(!bChecked)
			ToggleCheck();
		for each(auto c in pGroup->mControls)
		{
			if (c.second->GetControlType() == RADIO && c.second != this)
			{
				reinterpret_cast<CXRadioButton*>(c.second)->SetCheck(false);
			}
		}
	}
	return 0;
}

void CXRadioButton::AttachGroup(XID xGroupID, CXControls * pControls)
{
	this->xGroupID = xGroupID;
	this->pGroup = new CXControlGroup(pControls->GetOwner());
	bInGroup = true;
}

void CXRadioButton::AttachGroup(CXControlGroup * pGroup)
{
	this->pGroup = pGroup;
	xGroupID = pGroup->GetGroupID();
	bInGroup = true;
}
