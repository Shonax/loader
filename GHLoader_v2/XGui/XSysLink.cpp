#include "XSysLink.h"



CXSysLink::CXSysLink(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont)
	: CXControl(pOwner, xID, SYSLINK, x, y, w, h, szText, pFont)
{
	szClass = WC_LINK;
	SetStyle(WS_VISIBLE | WS_CHILD | WS_TABSTOP | LWS_TRANSPARENT);
}


CXSysLink::~CXSysLink()
{
}

bool CXSysLink::Create()
{
	bool bRet = CXControl::Create();

	return bRet;
}

void CXSysLink::OnNotify(UINT code, LPARAM lParam)
{
	switch (((LPNMHDR)lParam)->code)
	{
		case NM_CLICK:
		case NM_RETURN:
		{
			PNMLINK pNMLink = (PNMLINK)lParam;
			LITEM lItem = pNMLink->item;

			if ((((LPNMHDR)lParam)->hwndFrom == hWnd) && (lItem.iLink == 0))
			{
				ShellExecute(NULL, L"open", lItem.szUrl, NULL, NULL, SW_SHOW);
			}

			break;
		}
	}
}
