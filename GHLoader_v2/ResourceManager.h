#pragma once
#include "stdafx.h"

class CResource
{
public:
	CResource(int resID, int resType, std::vector<byte> & vResource);
	BOOL Update(HANDLE hUpdate);
	int GetID();
	int GetType();

private:
	HANDLE hUpdate;
	int resID;
	int resType;
	std::vector<byte> & vResource;
};

class CResourceManager
{
	HANDLE hUpdate;
	std::vector<CResource*> vResources;

public:
	CResourceManager();
	CResourceManager(std::vector<CResource*> vResources);
	~CResourceManager();

	// Update resources in a binary
	HANDLE BeginUpdate(tstring szFilePath);
	void AddResource(CResource * res);
	BOOL UpdateResources();
};

