#pragma once
#include "XControl.h"

#define WS_XLISTVIEW WS_CHILD | LVS_REPORT | LVS_EDITLABELS

class CXListViewItem
{
	int iItem = 0, iSubItem = 0;
	tstring szText;
	LVITEM lvi{ 0 };
	HICON hIcon = NULL;
	CXListViewItem * xSubItem = nullptr;
	std::vector<CXListViewItem*> vSubItems;

public:
	CXListViewItem() = default;
	CXListViewItem(int iItem, int iSubItem, tstring szText);
	CXListViewItem(int iItem, int iSubItem, tstring szText, HICON hIcon);

	LVITEM& GetItem();
	std::vector<CXListViewItem*> GetSubItems();
	void AddSubItem(int iItem, int iSubItem, tstring szText);
	CXListViewItem* GetSubItem(int iSubItem);
	int GetItemIndex();
	void SetText(tstring szText);
	tstring GetText();
	HICON GetIconHandle();
};

class CXListView : public CXControl
{
public:
	CXListView(CXWindow * pOwner, XID xID, int x, int y, int w, int h, tstring szText, CXFont * pFont = nullptr);
	~CXListView();

	virtual bool Create();
	virtual void OnNotify(UINT code, LPARAM lParam);
	bool InsertColumn(tstring szText);
	bool InsertColumn(tstring szText, int width);
	bool AddItem(int iItem, int iSubItem);
	bool AddItem(CXListViewItem & xListViewItem);
private:
	int iCol = 0;
	std::map<int, CXListViewItem> mListItems;
	HIMAGELIST hSmall;
};

