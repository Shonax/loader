#pragma once
#include "XControl.h"
#include <Richedit.h>
#define WS_XRICHTEXT ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_TABSTOP

class CXRichText : public CXControl
{
public:
	CXRichText(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXRichText();

	//virtual bool Create();
	virtual void SetBgColor(COLORREF color);
	virtual void SetTxtColor(COLORREF color);
};

