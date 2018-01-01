#pragma once
#include "XControl.h"
class CXBitmap :
	public CXControl
{
public:
	CXBitmap(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXBitmap();

	bool Load(HBITMAP hBitmap);
	virtual LRESULT OnDrawItem(WPARAM wParam, LPARAM lParam);

private:
	HBITMAP hBitmap;
};

