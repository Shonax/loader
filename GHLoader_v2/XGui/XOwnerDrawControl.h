#pragma once
#include "XControl.h"

#define BS_XOWNERDRAW (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW)

LRESULT CALLBACK OwnerDrawProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

class CXOwnerDrawControl :	public CXControl
{
public:
	CXOwnerDrawControl(CXWindow * pOwner, XID xID, ECXControl ControlType, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXOwnerDrawControl();

	virtual bool Create();
	virtual int OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void SetText(tstring szText);
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnCtlColor(WPARAM wParam, LPARAM lParam);
	virtual void Draw(HTHEME hTheme, LPDRAWITEMSTRUCT lpDI);

	virtual void RedrawCheck();
	virtual void SetCheck(bool bCheck);
	virtual bool GetCheck();
	virtual void ToggleCheck();
	virtual void SetHot(bool isHot);
private:
	void DetermineTypeAndState(int & iButtonPart, DWORD & dwState);

protected:
	DWORD dwDTFlags = DT_LEFT | DT_SINGLELINE;
	bool bChecked = false;
	bool bHot = false;
};

extern std::map<XID, CXOwnerDrawControl*> mODControls;