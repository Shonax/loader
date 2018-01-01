#pragma once
#include "XOwnerDrawControl.h"

class CXControls;

class CXGroupBox :	public CXOwnerDrawControl
{
public:
	CXGroupBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXGroupBox();
	virtual bool Create();
	void SetControlManager(CXControls* pControls);
	//virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);
	////virtual void Draw(HTHEME hTheme, LPDRAWITEMSTRUCT lpDI);
	//void Paint(LPDRAWITEMSTRUCT lpDI);
	void AddControl();

	CXControls * pControls = nullptr;
private:
	COLORREF clBorder;
	HPEN hBorderPen;
};

