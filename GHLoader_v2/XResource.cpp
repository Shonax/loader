#include "XResource.h"

CXResource::CXResource(HINSTANCE hInstance)
{
	this->hInstance = hInstance;
}

CXResource::~CXResource()
{
}

void * CXResource::GetPtrToData(DWORD dwID, DWORD dwType)
{
	hRsrc = FindResource(hInstance, MAKEINTRESOURCE(dwID), MAKEINTRESOURCE(dwType));
	if (!hRsrc)
		return nullptr;

	hGlobal = LoadResource(hInstance, hRsrc);
	if (!hGlobal)
		return nullptr;

	size = SizeofResource(hInstance, hRsrc);
	pResource = LockResource(hGlobal);
	if (pResource)
		return pResource;
	return nullptr;
}

CResourceWriter::CResourceWriter(HINSTANCE hInstance)
	: CXResource(hInstance)
{
}

CResourceWriter::~CResourceWriter()
{
}

size_t CResourceWriter::Write(tstring szFilename, DWORD dwID, DWORD dwType)
{
	GetPtrToData(dwID, dwType);

	if (pResource)
	{
		hFile = CreateFile(szFilename.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile)
		{
			DWORD outSize = 0;
			WriteFile(hFile, pResource, size, &outSize, nullptr);
			CloseHandle(hFile);
			return outSize;
		}
		CloseHandle(hFile);
	}
	return 0;
}

CResourceReader::CResourceReader(HINSTANCE hInstance)
	: CXResource(hInstance)
{
}


CResourceReader::~CResourceReader()
{
}

ResourceDataVec & CResourceReader::ReadIntoVector(DWORD dwID, DWORD dwType)
{
	if (!pResource)
		GetPtrToData(dwID, dwType);
	vData.resize(size);
	memcpy(&vData[0], pResource, size);
	return vData;
}
