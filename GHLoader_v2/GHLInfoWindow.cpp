#include "GHLInfoWindow.h"
#include "XResource.h"
#include "resource.h"

GHLInfoWindow::GHLInfoWindow(CXWindow * pOwner)
	: CXDialog(pOwner, 1, pOwner->GetPos().x + pOwner->GetWidth(), pOwner->GetPos().y, INFOWND_W, INFOWND_H, _T("Info..."))
{
}

GHLInfoWindow::GHLInfoWindow(CXWindow * pOwner, int x, int y)
	: CXDialog(pOwner, 1, x, y, INFOWND_W, INFOWND_H, _T("Info..."))
{
}

GHLInfoWindow::~GHLInfoWindow()
{
}

void GHLInfoWindow::Show()
{
	if (!bShown)
	{
		if (!hWnd)
		{
			Create();
			CreateControls();
		}
		RECT & rcWindow = pOwnerWindow->GetWndRect();
		SetPos(rcWindow.right - ((rcWindow.right  - rcWindow.left) / 2) - (uWidth / 2), rcWindow.top);
		CXDialog::Show();
	}
}


void GHLInfoWindow::GetInfoText()
{
	CResourceReader rr(hInstance);
	auto v = rr.ReadIntoVector(IDR_TEXTFILE1, TEXTFILE);
	
#ifdef _UNICODE
	if (!IsTextUnicode(v.data(), v.size(), NULL))
		szInfo = MBS2WCS((char*)v.data());
	else
		szInfo = (wchar_t*)v.data();
#else
	if (IsTextUnicode(v.data(), v.size(), NULL))
		szInfo = WCS2MBS((wchar_t*)v.data());
	else
		szInfo = (char*)v.data();
#endif
}

void GHLInfoWindow::CreateControls()
{
	if (szInfo.empty())
		GetInfoText();

	CXEdit * pEdit = 
		xControls->AddControl<CXEdit>(
			IDC_INFOEDIT, 
			5, 
			5, 
			rcRect.right - 10, 
			rcRect.bottom - 10, 
			/*L"This is going to be additional info\r\nthat muhfuckas can provide about\r\ntheir bullshit hack."*/szInfo);

	pEdit->SetStyle(WS_XEDITML);
}
