#include "GHLoader.h"
#include "Utility.h"

void LoaderCallback(GHLoader* ghLoader)
{
	ghLoader->LoadCheat();
}

GHLoader::GHLoader(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
	// create main window object and load form info from resource.
	ReadLoaderInfo();
	pWnd = new GHLMainWindow(hInstance, &loaderInfo);
	pWnd->CreateControls();

	//should probably start looking for the process we're interested in
	//we'll also need to load this info from resource file.
	//along with the dll we'll be injecting.
	szTarget = MBS2WCS(loaderInfo.loadSettings.szProcessName);
	thLoad = std::thread(LoaderCallback, this);
	thLoad.detach();
}


GHLoader::~GHLoader()
{
}

bool GHLoader::IsDlgMessage(MSG * pMsg)
{
	bool bIsDlgMsg = false;
	for (auto p : vWindows)
		bIsDlgMsg = bIsDlgMsg || IsDialogMessage(p->GetHandle(), pMsg);
	return bIsDlgMsg;
}

void GHLoader::LoadCheat()
{
	using namespace std::chrono_literals;
	//this function is called from another thread.
	//modifies a few labels and shit, nothing crazy. no need to worry about race conditions right now... i think :P
	cpProcess = pm.FindProcess(szTarget);
	
	CXLabel * pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_SEARCH);
	pLabel->SetText(L"Found process, injecting...");
	pLabel->SetTxtColor(RGB(255, 50, 50));

	pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_GAME);
	pLabel->SetTxtColor(RGB(0, 150, 255));

	//write necessary files to disk
	WriteFiles();
	
	//execute injector
	//there's no real way to get feedback (that i know of) from the injector like this
	//since we're just writing his executable to disk
	//we're stuck to just simply relying on broihons messageboxes :(
	//while sacrificing feedback, we retain the ability of adding an easy to implement update function.
	uint iDelay = loaderInfo.injSettings.iDelay;
	std::chrono::milliseconds delay(iDelay);
	std::this_thread::sleep_for(delay);
	Inject(); 

	// say good bye
	pLabel = pWnd->GetControls()->GetControl<CXLabel>(IDC_SEARCH);
	pLabel->SetText(L"Hack Loaded!");
	pLabel->SetTxtColor(RGB(50, 230, 50));
	
	std::this_thread::sleep_for(3s);
		
	pLabel->SetText(L"Closing loader... Have fun!");
	pLabel->SetTxtColor(RGB(200, 200, 200));
	
	Cleanup();

	std::this_thread::sleep_for(5s);
	ExitProcess(0);
}

template <class T>
size_t ReadFromResource(byte* pData, T & pBuffer)
{
	pBuffer = *(T*)pData;
	return sizeof(T);
}

size_t ReadStringFromResource(byte* pData, uint & uStrLen, std::string & szBuffer)
{
	uStrLen = *(uint*)pData;
	szBuffer = (char*)(pData + sizeof(uint));
	return sizeof(uint) + szBuffer.length() + 1;
}

LoaderInfo GHLoader::ReadLoaderInfo()
{
	CResourceReader rr(hInstance);
	auto vData = rr.ReadIntoVector(IDR_LOADERINFO1, LOADERINFO);

	//std::string szBuffer;
	//loaderInfo.formInfo.uFormTitleLen = *(uint*)&vData[0];	
	//loaderInfo.formInfo.szFormTitle = MBS2WCS(std::string((char*)&vData[sizeof(uint)]));
	
	//form info
	uint uCounter = ReadStringFromResource(&vData[0], loaderInfo.formInfo.uFormTitleLen, loaderInfo.formInfo.szFormTitle);
	uCounter += ReadStringFromResource(&vData[uCounter], loaderInfo.formInfo.uGameTitleLen, loaderInfo.formInfo.szGameTitle);
	uCounter += ReadStringFromResource(&vData[uCounter], loaderInfo.formInfo.uAuthorLen, loaderInfo.formInfo.szAuthor);
	//loader settings.... lol
	uCounter += ReadStringFromResource(&vData[uCounter], loaderInfo.loadSettings.uProcNameLen, loaderInfo.loadSettings.szProcessName);
	uCounter += ReadFromResource<BOOL>(&vData[uCounter], loaderInfo.loadSettings.bRandomNames);
	uCounter += ReadFromResource<BOOL>(&vData[uCounter], loaderInfo.loadSettings.bUPX);

	uCounter += ReadFromResource<uint>(&vData[uCounter], loaderInfo.injSettings.iInjMethod);
	uCounter += ReadFromResource<uint>(&vData[uCounter], loaderInfo.injSettings.iLaunchMethod);
	uCounter += ReadFromResource<BOOL>(&vData[uCounter], loaderInfo.injSettings.bHideDebug);
	uCounter += ReadFromResource<uint>(&vData[uCounter], loaderInfo.injSettings.iPEHMethod);
	uCounter += ReadFromResource<BOOL>(&vData[uCounter], loaderInfo.injSettings.bShiftMod);
	uCounter += ReadFromResource<BOOL>(&vData[uCounter], loaderInfo.injSettings.bCleanDD);
	uCounter += ReadFromResource<BOOL>(&vData[uCounter], loaderInfo.injSettings.bUnlinkPEB);
	uCounter += ReadFromResource<uint>(&vData[uCounter], loaderInfo.injSettings.iDelay);
	return loaderInfo;
}

void GHLoader::WriteFiles()
{
	CResourceWriter rw(hInstance);

	if (loaderInfo.loadSettings.bRandomNames)
	{
		RandomString rs(RandomNumber::Generate<int>(6, 16));
		szInj = rs.Generate();
		szInj.pop_back();
		szInj += (_T(".exe"));
		szDll = rs.Generate();
		szDll.pop_back();
		szDll += (_T(".dll"));
	}
	else
	{
		szInj = _T("inj.exe");
		szDll = _T("payload.dll");
	}
	
	rw.Write(szInj, IDINJ, BINARY);
	rw.Write(szDll, IDCHEAT, BINARY);
}

void GHLoader::Inject()
{
	//get proc id and parse it to a string
	DWORD pid = cpProcess.GetPID();
	tstring szPid(22, 0);
	_itot_s(pid, &szPid[0], 22, 10);
	
	tstring szParam = _T("/p ");
	szParam.append(szPid.c_str()); 
	szParam.append(_T(" /f \""));
	szParam.append(szDll);
	szParam.append(_T("\" /m "));


	char buf[10]{ 0 };
	itoa(loaderInfo.injSettings.iInjMethod, &buf[0], 10);
	szParam.append(MBS2WCS(buf));
	szParam.append(_T(" /o "));

	DWORD dwFlags = 0;

	switch (loaderInfo.injSettings.iPEHMethod)
	{
		case 1:
			dwFlags |= INJ_ERASE_HEADER;
			break;
		case 2:
			dwFlags |= INJ_FAKE_HEADER;			
			break;
	}

	if (loaderInfo.injSettings.bUnlinkPEB)
		dwFlags |= INJ_UNLINK_FROM_PEB;

	if (loaderInfo.injSettings.bShiftMod)
		dwFlags |= INJ_SHIFT_MODULE;

	if (loaderInfo.injSettings.bCleanDD)
		dwFlags |= INJ_CLEAN_DATA_DIR;

	if (loaderInfo.injSettings.bHideDebug)
		dwFlags |= INJ_HIDE_THREAD_FROM_DEBUGGER;

	ZeroMemory(buf, 10);
	tstring tBuf(10, 0);
	_itot_s((int)dwFlags, &tBuf[0], 10, 10);
	szParam.append(tBuf.c_str());
	szParam.append(_T(" /l "));
	tBuf.clear();
	_itot_s(loaderInfo.injSettings.iLaunchMethod, &tBuf[0], 10, 10);
	szParam.append(tBuf.c_str());

	//CResourceWriter rw(hInstance);
	//rw.Write(L"loader.bin", IDR_LOADERINFO1, LOADERINFO);

	ShellExecute(NULL, NULL, szInj.c_str(), szParam.c_str(), NULL, SW_HIDE);
}

void GHLoader::Cleanup()
{
	DeleteFile(szDll.c_str());
	DeleteFile(szInj.c_str());
}
