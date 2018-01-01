#include "XMainWindow.h"
#define IDEDIT1			0x7000
#define IDBUTTON1		0x8000
#define IDLABEL1		0x8050
#define IDRADIO1		0x9000
#define IDRADIO2		0x9001
#define IDCHECK1		0x9901
#define IDLISTBOX0		0x7901
#define IDCOMBO0		0x9999

#define IDTABCONTROL0	0x5550
#define IDGROUP0RADIO0	0x9550
#define IDTRACKBAR0		0x6666
#define IDSYSLINK0		0x3333

CXMainWindow * g_pMainWindow = nullptr;
CXControls * g_pControls = nullptr;

BOOL WINAPI EnumChildProc(HWND hWnd, LPARAM lParam);

bool bIsTracked = false;
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			if (g_pControls)
			{
				CXButton * pButton = g_pControls->GetControl<CXButton>(IDBUTTON1);
				//if (pButton)
				//{
				//	pButton->SetText(_T("Changed"));
				//}
			}
			break;
		}
		case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			g_pControls->mControls[id]->OnCommand(wParam, lParam);
			return 0;
		}
		case WM_DRAWITEM:
		{
			if (g_pControls)
				return g_pControls->mControls[wParam]->OnDrawItem(wParam, lParam);
			break;
		}
		case WM_PAINT:
		{
			g_pMainWindow->OnPaint();
			break;
		}
		case WM_CTLCOLOR:
		case WM_CTLCOLORBTN:
		case WM_CTLCOLORSTATIC:
		{
			int id = GetDlgCtrlID((HWND)lParam);
			return g_pControls->mControls[id]->OnCtlColor(wParam, lParam);
			//return LRESULT(GetStockObject(HOLLOW_BRUSH));
		}
		case WM_NOTIFY:
		{
			NMHDR * pNMHDR = (NMHDR*)lParam;

			int id = pNMHDR->idFrom;
			if(id > 1)
			g_pControls->mControls[id]->OnNotify(pNMHDR->code, lParam);


			break;
		}
		case WM_MOUSEMOVE:
		{
			break;
		}
		case WM_MOUSEHOVER:
		{
			break;
		}
		case WM_MOUSELEAVE:
		{
			break;
		}
		case WM_DESTROY:
		{
			DestroyWindow(g_pMainWindow->GetHandle());
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL WINAPI EnumChildProc(HWND hWnd, LPARAM lParam)
{
	POINT p;
	p.x = LOWORD(lParam);
	p.y = HIWORD(lParam);
	int id = GetDlgCtrlID(hWnd);
	g_pControls->mControls[id]->OnHover(p);
	RedrawWindow(g_pControls->mControls[id]->GetHandle(), NULL, NULL, RDW_INVALIDATE);
	return TRUE;
}

CXMainWindow::CXMainWindow(HINSTANCE hInstance, tstring szTitle, tstring szClass, int x, int y, int w, int h)
	: CXWindow(hInstance, MainWndProc),
	RadioGroup(this)
{
	SetText(szTitle);
	SetClass(szClass);
	SetPos(x, y);
	SetWidth(w);
	SetHeight(h);
	SetStyle(WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	hBgr = GetStockBrush(WHITE_BRUSH);
}


CXMainWindow::~CXMainWindow()
{
}

bool CXMainWindow::Create()
{
	LoadLibrary(TEXT("Msftedit.dll")); // for rich text edit controls iirc
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_TAB_CLASSES | ICC_LISTVIEW_CLASSES | ICC_LINK_CLASS;
	if (!InitCommonControlsEx(&icc))
		return false;

	WNDCLASSEX wcx = CreateBasicClass(szClass);
	RegisterClassEx(&wcx);
	if (!CreateXWindow())
		return false;
	
	GetWndRect();

	//Create control manager
	pControls = new CXControls(this);
	g_pControls = pControls;
	return true;
}



void CXMainWindow::OnPaint()
{
	if((HBRUSH)GetClassLong(hWnd, GCLP_HBRBACKGROUND) != hBgr)	//
		SetClassLong(hWnd, GCLP_HBRBACKGROUND, (LONG)hBgr);		// i don't think i even need this... 
	
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	//do stuff.
	EndPaint(hWnd, &ps);
	
	bUpdate = false; //don't know if i'll really need this
}

LRESULT CXMainWindow::OnEraseBkgrnd(WPARAM wParam)
{
	return 1;
}
