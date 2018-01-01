#pragma once
#include "XButton.h"
#include "XEdit.h"
#include "XRadioButton.h"
#include "XCheckBox.h"
#include "XListBox.h"
#include "XGroupBox.h"
#include "XTabControl.h"
#include "XRichText.h"
#include "XListView.h"
#include "XComboBox.h"
#include "XTrackBar.h"
#include "XSysLink.h"
#include "XLabel.h"
#include "XDialog.h"
#include "XBitmap.h"

class CXControlGroup;

class CXControls
{
public:
	CXControls();
	CXControls(CXWindow * pOwner);
	~CXControls();
	
	CXWindow* GetOwner();


	//template <class T>
	//int AddControl(T* t);

	int AddControl(CXControl* pControl);

	template <class T>
	T* AddControl(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);

	template <class T>
	int AddControlToGroup(XID xGroupID, XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);

	void AddGroup(XID xGroupID);
	void AddGroup(CXControl* pControl);

	void AddButton(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	void AddEdit(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	void AddRadio(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	void AddCheckBox(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	template <class T>
	bool GetControl(XID id, T * pControlOut);

	template <class T>
	T* GetControl(XID id);

private:
	CXWindow * pOwner = nullptr;
	RECT rcClient;
protected:
	bool bIsGroup = false;
public:
	std::map<XID, CXControl*> mControls;
	std::map<XID, CXControlGroup*> vGroups;
};

//template<class T>
//inline int CXControls::AddControl(T* t)
//{
//	mControls[id] = t;
//	GetControl<CXControl>(id)->Create();
//	return 0;
//}

template<class T>
inline T* CXControls::AddControl(XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont)
{
	RECT rc = { x, y, w, h };
	AdjustWindowRect(&rc, WS_VISIBLE | WS_CHILD, FALSE);
	mControls[id] = new T(pOwner, id, rc.left, rc.top, rc.right, rc.bottom, szText, pFont);
	//mControls[id] = new T(pOwner, id, x, y, w, h, szText, pFont);
	T* pControl = GetControl<T>(id);
	pControl->Create();
	return pControl;
}

template<class T>
inline int CXControls::AddControlToGroup(XID xGroupID, XID id, int x, int y, int w, int h, tstring szText, CXFont * pFont)
{
	int iRet;
	//in case you're grouping radio buttons on the main window and not in a groupbox control.
	if (bIsGroup)
	{
		mControls[id] = new T(pOwner, id, x, y, w, h, szText, pFont);
		iRet = vGroups[xGroupID]->AddControl(mControls[id]);
	}
	else
		iRet = vGroups[xGroupID]->AddControl<T>(id, x, y, w, h, szText, pFont);

	CXControl* pControl = vGroups[xGroupID]->GetControl<T>(id);
	if (pControl->GetControlType() == RADIO)
		reinterpret_cast<CXRadioButton*>(pControl)->AttachGroup(vGroups[xGroupID]);
	return iRet;
}

template<class T>
inline bool CXControls::GetControl(XID id, T * pControlOut)
{
	CXControl* pControl = mControls[id];
	if(!pControl)
		return false;

	pControlOut = (T*)pControl;
}

template<class T>
inline T* CXControls::GetControl(XID id)
{
	if (!mControls.empty())
	{
		T* pPtr = reinterpret_cast<T*>(mControls[id]);
		return pPtr;
	}
	return nullptr;
}

class CXControlGroup : public CXControls
{
	XID xGroupID;
	
public:
	CXControlGroup(CXWindow * pOwner)
		:CXControls(pOwner)
	{
		xGroupID = pOwner->GetID();
		bIsGroup = true;
	}

	XID GetGroupID();
};