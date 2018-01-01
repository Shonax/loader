#pragma once
#include "XWindow.h"
#include "XControls.h"

#define XMAINWNDCLS _T("XMainWindowClass000")

class CXMainWindow : public CXWindow
{
public:
	CXMainWindow(HINSTANCE hInstance, tstring szTitle, tstring szClass, int x, int y, int w, int h);
	~CXMainWindow();

	bool Create();
	
	void OnPaint();
	LRESULT OnEraseBkgrnd(WPARAM wParam);

protected:
	CXControls* pControls = nullptr;
	CXControlGroup RadioGroup;

private:
	bool bUpdate = true;
};

extern CXMainWindow * g_pMainWindow;