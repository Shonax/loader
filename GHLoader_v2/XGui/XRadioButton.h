#pragma once
#include "XOwnerDrawControl.h"

#define BS_XRADIO BS_XOWNERDRAW

class CXControls;
class CXControlGroup;

class CXRadioButton : public CXOwnerDrawControl
{
	CXControlGroup* pGroup = nullptr;
	XID xGroupID;
	bool bInGroup = false;
public:
	CXRadioButton(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXRadioButton();

	virtual bool Create();
	virtual int OnCommand(WPARAM wParam, LPARAM lParam);
	void AttachGroup(XID xGroupID, CXControls * pControls);
	void AttachGroup(CXControlGroup* pGroup);
};

