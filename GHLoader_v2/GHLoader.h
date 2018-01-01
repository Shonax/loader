#pragma once
#include "GHLMainWindow.h"
#include "ProcManager.h"
#include "XResource.h"
#include "RandomString.h"
#include "RandomNumber.h"

#define INJ_ERASE_HEADER				0x01
#define INJ_FAKE_HEADER					0x02
#define INJ_UNLINK_FROM_PEB				0x04
#define INJ_SHIFT_MODULE				0x08
#define INJ_CLEAN_DATA_DIR				0x10
#define INJ_HIDE_THREAD_FROM_DEBUGGER	0x20

class GHLoader
{
public:
	GHLoader(HINSTANCE hInstance);
	~GHLoader();

	bool IsDlgMessage(MSG * pMsg);
	void LoadCheat();

private:
	LoaderInfo ReadLoaderInfo();
	void WriteFiles();
	void Inject();
	void Cleanup();
private:
	std::vector<CXWindow*> vWindows;
	HINSTANCE hInstance;
	GHLMainWindow * pWnd;
	LoaderInfo loaderInfo;
	
	ProcManager pm;
	std::thread thLoad;
	tstring szTarget;
	CProcess cpProcess;
	tstring szInj;
	tstring szDll;
};

