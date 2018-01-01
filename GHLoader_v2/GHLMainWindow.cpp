#include "GHLMainWindow.h"
#include "Utility.h"

void ShowInfoWnd(uintptr_t pWnd)
{
	((GHLInfoWindow*)pWnd)->Show();
}

GHLMainWindow::GHLMainWindow(HINSTANCE hInstance, LoaderInfo * li)
	: CXMainWindow(hInstance, MBS2WCS(li->formInfo.szFormTitle), XMAINWNDCLS, 250, 150, 400, 300)
{
	g_pMainWindow = this;
	SetBgColor(RGB(25,25,25));
	SetStyle(WS_VISIBLE | WS_SYSMENU);

	this->hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	this->hIconSm = hIcon;

	if (!Create())
	{
		//error ;P
		exit(-1);
	}

	xfSearch = CXFont(_T("Consolas"), 18);
	//xfSearch.SetWeight(FW_SEMIBOLD);

	xfGameName = CXFont(_T("Agency FB"), 48);
	xfGameName.SetItalic(TRUE);

	int x = rcWindow.right - ((rcWindow.right - rcWindow.left) / 2);
	pInfoWnd = new GHLInfoWindow(this, x, rcWindow.top);
	loaderInfo = li;
}

GHLMainWindow::~GHLMainWindow()
{
}

#define TT(s) MBS2WCS(s)
int GHLMainWindow::CreateControls()
{
	CXLabel * pSearching =
		pControls->AddControl<CXLabel>(
			IDC_SEARCH,
			rcRect.left,
			rcRect.top + 10,
			uWidth-5,
			30,
			_T("Searching for process..."),
			&xfSearch);

	CXLabel * pGameName =
		pControls->AddControl<CXLabel>(
			IDC_GAME,
			rcRect.left,
			rcRect.top + 40,
			uWidth-5,
			uHeight / 5,
			TT(loaderInfo->formInfo.szGameTitle).c_str(),
			&xfGameName);

	tstring szAuthor = _T("Author: ");
	szAuthor += TT(loaderInfo->formInfo.szAuthor);
	CXLabel* pAuthor =
		pControls->AddControl<CXLabel>(
			IDC_LABEL,
			rcRect.left,
			rcRect.top + 100,
			uWidth-5,
			30,
			szAuthor.c_str());

	CXButton * pInfo =
		pControls->AddControl<CXButton>(
			IDB_INFO,
			(rcRect.right / 2) - 65,
			rcRect.top + 140,
			140,
			30,
			_T("More Info"));

	pInfo->SetAction(*(new std::function<void(uintptr_t)>(ShowInfoWnd)));
	pInfo->SetCommandArgs((uintptr_t)pInfoWnd);

	//HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"banner.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP hBmp = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
	pControls->AddControl<CXBitmap>(IDC_BANNER, 0, rcRect.bottom - 75, rcRect.right, 75, L"");
	pControls->GetControl<CXBitmap>(IDC_BANNER)->Load(hBmp);

	pGameName->SetDrawFlags(DT_NOCLIP | DT_CENTER);
	pGameName->SetTxtColor(RGB(255, 200, 0));
	//pGameName->SetTxtColor(RGB(0, 150, 255));
	
	pSearching->SetDrawFlags(DT_NOCLIP | DT_CENTER);
	pSearching->SetTxtColor(RGB(200, 200, 200));
	//pSearching->SetTxtColor(RGB(50, 230, 50));

	pAuthor->SetDrawFlags(DT_NOCLIP | DT_CENTER);
	pAuthor->SetTxtColor(RGB(225, 225, 225));
	//pInfo->SetDrawFlags(DT_NOCLIP | DT_CENTER);

	return 0;
}

CXControls * GHLMainWindow::GetControls()
{
	return this->pControls;
}
