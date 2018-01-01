#pragma once
#include "XOwnerDrawControl.h"
class CXCheckBox :	public CXOwnerDrawControl
{
public:
	CXCheckBox(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXCheckBox();

	//virtual bool Create();
};

