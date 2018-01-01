#pragma once
#include "XWindow.h"

#define XFDOPENFLAG OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY
#define XFDSAVEFLAG OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT

enum EXFILEDIALOGMODE
{
	OPEN,
	SAVE
};

class CXFileDialogFilterEntry
{
public:
	CXFileDialogFilterEntry(tstring szDesc, tstring szExt);
	std::vector<TCHAR>& GetData();
private:
	void BuildVector();
private:
	std::vector<TCHAR> vData;
	tstring szDesc;
	tstring szExt;
};

class CXFileDialog
{
public:
	CXFileDialog(CXWindow * pOwner, EXFILEDIALOGMODE dialogMode, CXFileDialogFilterEntry * pFilter);	
	~CXFileDialog();

	virtual bool Show(tstring & szPath);
	virtual tstring GetFileName();

private:
	CXWindow * pOwner = nullptr;
	EXFILEDIALOGMODE fdMode;
	OPENFILENAME ofn;
	tstring szFilter; 
	tstring szDefExt;
	tstring szFileName;
};

