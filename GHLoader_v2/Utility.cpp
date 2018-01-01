#include "Utility.h"

std::wstring MBS2WCS(std::string szString)
{
	size_t cc;
	std::wstring szBuf(szString.length() * 2, 0);
	mbstowcs_s(&cc, &szBuf[0], szBuf.size(), szString.c_str(), szString.length());
	return szBuf.c_str();
}

std::string WCS2MBS(std::wstring szString)
{
	size_t cc;
	std::string szBuf(szString.length() * 2, 0);
	wcstombs_s(&cc, &szBuf[0], szBuf.size(), szString.c_str(), szString.length());
	return szBuf.c_str();
}

