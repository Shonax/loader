#pragma once
#include <stdafx.h>

typedef std::vector<byte> ResourceDataVec;

class CXResource
{
public:
	CXResource(HINSTANCE hInstance);
	~CXResource();

public:
	void * GetPtrToData(DWORD dwID, DWORD dwType);

protected:
	HINSTANCE hInstance;
	HRSRC hRsrc = NULL;
	HGLOBAL hGlobal = NULL;
	size_t size = 0;
	void* pResource = nullptr;
	HANDLE hFile = NULL;
};

class CResourceWriter : public CXResource
{
public:
	CResourceWriter(HINSTANCE hInstance);
	~CResourceWriter();
	size_t Write(tstring szFilename, DWORD dwID, DWORD dwType);

};

class CResourceReader : public CXResource
{
public:
	CResourceReader(HINSTANCE hInstance);
	~CResourceReader();
	ResourceDataVec & ReadIntoVector(DWORD dwID, DWORD dwType);

private:
	ResourceDataVec vData;
};