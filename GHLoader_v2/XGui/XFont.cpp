#include "XFont.h"

CXFont::CXFont()
{
}

CXFont::CXFont(tstring szFace, int height, int width)
{
	this->szFace = szFace;
	this->iWidth = width;
	this->iHeight = height;
}

CXFont::~CXFont()
{
	if (hFont)
		DeleteObject(hFont);
}

HFONT CXFont::Create()
{
	if (bChanged || !hFont)
	{
		if (hFont)
			DeleteObject(hFont);

		hFont = CreateFont(this->iHeight,
			this->iWidth,
			0, 0,
			this->iWeight,
			this->bItalic,
			this->bUnderline,
			this->bStrikethrough,
			ANSI_CHARSET,
			OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,
			FF_DONTCARE,
			szFace.c_str());
	}
	return hFont;
}

HFONT CXFont::Reset()
{
	if (hFont)
	{
		DeleteObject(hFont);
	}
	bChanged = false;
	return Create();
}

HFONT CXFont::GetHandle()
{
	if (!hFont)
		Create();
	return hFont;
}

HFONT CXFont::SetFont(HDC hdc)
{
	if (!hFont)
		Create();
	hPrevFont = (HFONT)SelectObject(hdc, hFont);
	return hPrevFont;
}

void CXFont::SetPrevFont(HDC hdc)
{
	SelectObject(hdc, hPrevFont);
}

void CXFont::SetFace(tstring szFace)
{
	this->szFace = szFace;
	bChanged = true;
}

void CXFont::SetHeight(int height)
{
	this->iHeight = height;
	bChanged = true;
}

void CXFont::SetWidth(int width)
{
	this->iWidth = width;
	bChanged = true;
}

void CXFont::SetWeight(int weight)
{
	this->iWeight = weight;
	bChanged = true;
}

void CXFont::SetItalic(BOOL bItalic)
{
	this->bItalic = bItalic;
	bChanged = true;
}

void CXFont::SetStrikeOut(BOOL bStrike)
{
	this->bStrikethrough = bStrike;
	bChanged = true;
}

void CXFont::SetUnderline(BOOL bUnderline)
{
	this->bUnderline = bUnderline;
	bChanged = true;
}
