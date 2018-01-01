#pragma once
#include "Process.h"

//typedef std::map<int, std::unique_ptr<CProcess>> ProcMap;
//typedef std::vector<std::unique_ptr<CProcess>> ProcVec;

typedef std::map<int, CProcess*> ProcMap;
typedef std::vector<CProcess*> ProcVec;

enum class EPM_SortMethod
{
	DEFAULT,
	DEFAULTI,
	NAME,
	NAMEI,
	PID,
	PIDI
};

enum class EPM_SearchMethod
{
	PID,
	NAME
};

class ProcManager
{
public:
	ProcManager();
	~ProcManager();

	int ReloadProcs();
	int LoadProcs();
	ProcVec& GetProcs();
	CProcess FindProcess(tstring szProcessName);
	void TerminateScan();

public:
	ProcVec& Sort(EPM_SortMethod sortMethod);
private:
	ProcVec& SortByName(bool bInverted);
	ProcVec& SortByPID(bool bInverted);

private:
	ProcMap mProcs;
	ProcVec vProcs;
	bool bTerminateScans = false;
	bool bScansTerminated = false;
};

