#pragma once
#include "XFileDialog.h"
//#include "XControls.h"

#define WS_XDIALOG WS_VISIBLE | WS_SYSMENU

class CXControls;
typedef XID XDialogID;

class CXDialog : public CXWindow
{
public:
	CXDialog(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText);
	~CXDialog();

	virtual bool Create();
	virtual void Show();
	virtual void Destroy();
protected:
	CXControls* xControls;
	XDialogID xDialogID;
	bool bShown = false;
	bool bCloseOnEsc = true;
};


extern std::map<XDialogID, CXDialog*> mDialogs;
extern std::map<HWND, CXDialog*> mDialogsH;