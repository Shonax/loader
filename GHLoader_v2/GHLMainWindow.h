#pragma once
#include "XGui\XMainWindow.h"
#include "GHLInfoWindow.h"
#include "resource.h"

#define IDC_SEARCH	0x8000
#define IDC_GAME	0x8001
#define IDC_LABEL	0x8002
#define IDB_INFO	0x8003
#define IDC_BANNER	0x8010

#define IDINJ	IDR_BINARY1
#define IDCHEAT	IDR_BINARY2

//
//struct GHLFormInfo
//{
//	tstring szTitle;
//	tstring szProcess;
//	tstring szAuthor;
//	tstring szInfo;
//	int x, y, w, h;
//	COLORREF clCol;
//};
//

struct LoaderInfo
{
	struct FormInfo
	{
		uint uFormTitleLen = 0;
		std::string szFormTitle;
		uint uGameTitleLen = 0;
		std::string szGameTitle;
		uint uAuthorLen = 0;
		std::string szAuthor;
	}formInfo;

	struct LoadSettings
	{
		uint uProcNameLen = 0;
		std::string szProcessName;
		BOOL bRandomNames = FALSE;
		BOOL bUPX = FALSE;
	}loadSettings;

	struct InjSettings
	{
		uint iInjMethod = 0;
		uint iLaunchMethod = 0;
		BOOL bHideDebug = FALSE;
		uint iPEHMethod = 0;
		BOOL bShiftMod = FALSE;
		BOOL bCleanDD = FALSE;
		BOOL bUnlinkPEB = FALSE;
		uint iDelay = 0;
	}injSettings;
};

class GHLMainWindow : public CXMainWindow
{
public:
	GHLMainWindow(HINSTANCE hInstance, LoaderInfo * li);
	~GHLMainWindow();

	//we'll probably need to pass in some sort of struct
	//with some data to customize per build
	int CreateControls();
	CXControls* GetControls();
private:
	GHLInfoWindow * pInfoWnd;
	LoaderInfo * loaderInfo;
	CXFont xfSearch;
	CXFont xfGameName;
};

