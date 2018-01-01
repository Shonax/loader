#pragma once
#include "XControl.h"

#define BS_XBUTTON (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_CENTER)
#define BS_XBUTTONICON (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_ICON | BS_PUSHBUTTON | BS_CENTER)
#define BS_DEFXBUTTON (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_CENTER)

class CXButton : public CXControl
{
public:
	CXButton(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXButton();
	virtual bool Create();
	void SetCommandArgs(uintptr_t pArgs);
	virtual int OnCommand(WPARAM wParam, LPARAM lParam, uintptr_t pArg1);
	virtual int OnCommand(WPARAM wParam, LPARAM lParam);

	virtual int SetIcon(HICON hIcon);

private:
	HICON hIcon = NULL;
	uintptr_t pCommandArgs = 0;
};

