#include "ProcManager.h"



ProcManager::ProcManager()
{
}


ProcManager::~ProcManager()
{
}

int ProcManager::ReloadProcs()
{
	for (auto p : vProcs)
		delete p;
	mProcs.clear();
	vProcs.clear();
	return LoadProcs();
}

int ProcManager::LoadProcs()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!hSnap)
		return GetLastError();

	//need to come up with a way to safely terminate this scan cause it crashes on exit from time to time

	PROCESSENTRY32 pe32{ 0 };
	pe32.dwSize = sizeof(pe32);
	if (Process32First(hSnap, &pe32))
	{
		this->mProcs[vProcs.size()] = new CProcess(pe32);
		this->vProcs.push_back(mProcs[vProcs.size()]);
		while (Process32Next(hSnap, &pe32))
		{
			this->mProcs[vProcs.size()] = new CProcess(pe32);
			this->vProcs.push_back(mProcs[vProcs.size()]);
		}
	}
	else
		return GetLastError();
	return this->vProcs.size();
}

//rapidly becoming obsolete lol..
ProcVec& ProcManager::GetProcs()
{
	return vProcs;
}

CProcess ProcManager::FindProcess(tstring szProcessName)
{
	while (true)
	{
		if (bTerminateScans)
			break;
		if (vProcs.empty())
			LoadProcs();
		if (vProcs.size() == 0)
			break;

		for (auto p : vProcs)
		{
			if (lstrcmp(szProcessName.c_str(), p->GetProcName().c_str()))
				continue;

			return *p;
		}
		ReloadProcs();
	}
	return CProcess();
}

void ProcManager::TerminateScan()
{
	bTerminateScans = true;

	while (!bScansTerminated);
}

ProcVec& ProcManager::Sort(EPM_SortMethod sortMethod)
{
	//aight, so this should be fun.
	//we should probably change our vector to a map
	//obv change how we load the processes into the container
	//keep that container as is for the default order.
	vProcs.clear();
	switch (sortMethod)
	{
		case EPM_SortMethod::DEFAULT:
		{
			for (auto p : mProcs)
				vProcs.push_back(p.second);
			break;
		}
		case EPM_SortMethod::DEFAULTI:
		{
			for (int x = 0; x < mProcs.size(); x++)
				vProcs.push_back(mProcs[mProcs.size() - 1 - x]);
			break;
		}
		case EPM_SortMethod::NAME:
		{
			vProcs = SortByName(false);
			break;
		}
		case EPM_SortMethod::NAMEI:
		{
			vProcs = SortByName(true);
			break;
		}
		case EPM_SortMethod::PID:
		{
			vProcs = SortByPID(false);
			break;
		}
		case EPM_SortMethod::PIDI:
		{
			vProcs = SortByPID(true);
			break;
		}
	}

	return vProcs;
}

ProcVec & ProcManager::SortByName(bool bInverted)
{
	ProcVec vBuf;
	std::vector<tstring> vNames;

	for (auto p : mProcs)
		vBuf.push_back(p.second);
	
	for (auto p : vBuf)
		vNames.push_back(p->GetProcName());

	std::sort(vNames.begin(), vNames.end());
	
	vBuf.clear();

	for (auto name : vNames)
	{
		for (auto p : mProcs)
		{
			if (!lstrcmp(name.c_str(), p.second->GetProcName().c_str()))
			{
				vBuf.push_back(p.second);
				break;
			}
		}
	}	

	vProcs.clear();
	if (bInverted)
	{
		int bufSize = vBuf.size();
		for (int x = 0; x < bufSize; x++)
		{
			vProcs.push_back(vBuf[bufSize - 1 - x]);
		}
	}
	else
		vProcs = vBuf;
	return vProcs;
}

ProcVec & ProcManager::SortByPID(bool bInverted)
{
	ProcVec vBuf;
	std::vector<DWORD> vPIDs;

	for (auto p : mProcs)
		vBuf.push_back(p.second);

	for (auto p : vBuf)
		vPIDs.push_back(p->GetPID());

	std::sort(vPIDs.begin(), vPIDs.end());

	vBuf.clear();

	for (auto pid : vPIDs)
	{
		for (auto p : mProcs)
		{
			if (pid == p.second->GetPID())
			{
				vBuf.push_back(p.second);
				break;
			}
		}
	}

	vProcs.clear();
	if (bInverted)
	{
		int bufSize = vBuf.size();
		for (int x = 0; x < bufSize; x++)
		{
			vProcs.push_back(vBuf[bufSize - 1 - x]);
		}
	}
	else
		vProcs = vBuf;
	return vProcs;
}

