#include "Process.h"



CProcess::CProcess()
{
}

CProcess::CProcess(PROCESSENTRY32 pe32)
{
	this->pe32 = pe32;
	this->dwPID = pe32.th32ProcessID;
	this->szExe = pe32.szExeFile;
}

CProcess::CProcess(DWORD dwPID, tstring szExe)
{
	this->dwPID = dwPID;
	this->szExe = szExe;
}


CProcess::~CProcess()
{
	if (hHandle)
		CloseHandle(hHandle);
}

HANDLE CProcess::Open()
{
	return Open(PROCESS_ALL_ACCESS);
}

HANDLE CProcess::Open(DWORD dwAccess)
{
	hHandle = OpenProcess(dwAccess, FALSE, dwPID);
	if (!hHandle)
	{
		//GetLastError();
		return 0;
	}
	return hHandle;
}

tstring CProcess::GetProcName()
{
	return szExe;
}

tstring CProcess::GetProcPath()
{
	if (!hHandle)
		Open();

	if (hHandle)
	{
		szPath.resize(MAX_PATH);
		GetModuleFileNameEx(hHandle, NULL, &szPath[0], MAX_PATH);
	}
	else
		szPath = _T("Ehh... Iunno :D");
	
	return szPath;
}

DWORD CProcess::GetPID()
{
	return dwPID;
}
