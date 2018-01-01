#include "ResourceManager.h"

CResource::CResource(int resID, int resType, std::vector<byte> & vResource)
	:vResource(vResource)
{
	this->resID = resID;
	this->resType = resType;
}

BOOL CResource::Update(HANDLE hUpdate)
{
	return UpdateResource(hUpdate,
		MAKEINTRESOURCE(resType),
		MAKEINTRESOURCE(resID),
		DEFLANGID,
		&vResource[0],
		vResource.size());
}

int CResource::GetID()
{
	return resID;
}

int CResource::GetType()
{
	return resType;
}

CResourceManager::CResourceManager()
{
}

CResourceManager::CResourceManager(std::vector<CResource*> vResources)
{
	this->vResources = vResources;
}


CResourceManager::~CResourceManager()
{
}

HANDLE CResourceManager::BeginUpdate(tstring szFilePath)
{
	hUpdate = BeginUpdateResource(szFilePath.c_str(), FALSE);
	return hUpdate;
}

void CResourceManager::AddResource(CResource * res)
{
	this->vResources.push_back(res);
}

BOOL CResourceManager::UpdateResources()
{
	for each(auto rRes in vResources)
		rRes->Update(hUpdate);

	return EndUpdateResource(hUpdate, FALSE);
}
