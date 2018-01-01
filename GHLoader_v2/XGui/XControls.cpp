#include "XControls.h"



CXControls::CXControls()
{
}

CXControls::CXControls(CXWindow * pOwner)
{
	this->pOwner = pOwner;
	GetClientRect(pOwner->GetHandle(), &rcClient);
}


CXControls::~CXControls()
{
}

CXWindow * CXControls::GetOwner()
{
	return this->pOwner;
}

int CXControls::AddControl(CXControl * pControl)
{
	mControls[pControl->GetID()] = pControl;
	pControl->Create();
	return 0;
}

void CXControls::AddGroup(XID xGroupID)
{
	if (!xGroupID)
		this->bIsGroup = true;

	vGroups[xGroupID] = new CXControlGroup(pOwner);
}

void CXControls::AddGroup(CXControl * pControl)
{
	vGroups[pControl->GetID()] = new CXControlGroup(pControl);
}

void CXControls::AddButton(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont)
{
	mControls[id] = new CXButton(pOwner, id, x, y, w, h, szText, pFont);
	GetControl<CXButton>(id)->Create();
}

void CXControls::AddEdit(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont)
{
	mControls[id] = new CXEdit(pOwner, id, x, y, w, h, szText, pFont);
	GetControl<CXEdit>(id)->Create();
}

void CXControls::AddRadio(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont)
{
	mControls[id] = new CXRadioButton(pOwner, id, x, y, w, h, szText, pFont);
	GetControl<CXRadioButton>(id)->Create();
}

void CXControls::AddCheckBox(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont)
{
	mControls[id] = new CXCheckBox(pOwner, id, x, y, w, h, szText, pFont);
	GetControl<CXCheckBox>(id)->Create();
}

XID CXControlGroup::GetGroupID()
{
	return xGroupID;
}
