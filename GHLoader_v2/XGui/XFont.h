#pragma once
#include "stdafx.h"

class CXFont
{
public:
	CXFont();
	CXFont(tstring szFace, int height, int width = 0);
	~CXFont();
	HFONT Create();
	HFONT Reset();
	HFONT GetHandle();
	HFONT SetFont(HDC hdc);
	void SetPrevFont(HDC hdc);
	void SetFace(tstring szFace);
	void SetHeight(int height);
	void SetWidth(int width);
	void SetWeight(int weight);
	void SetItalic(BOOL bItalic);
	void SetStrikeOut(BOOL bStrike);
	void SetUnderline(BOOL bUnderline);

private:
	tstring szFace;
	HFONT hFont = NULL;
	HFONT hPrevFont = NULL;
	int iHeight = 0;
	int iWidth = 0;
	int iWeight = 0;
	BOOL bItalic = FALSE;
	BOOL bStrikethrough = FALSE;
	BOOL bUnderline = FALSE;
	bool bChanged = false;
};