#pragma once
#include <stdafx.h>



typedef int XID;

class CXWindow
{
public:
	CXWindow(HINSTANCE hInstance);
	CXWindow(HINSTANCE hInstance, WNDPROC WndProc);
	CXWindow(HINSTANCE hInstance, WNDPROC WndProc, RECT rcRect);
	CXWindow(HINSTANCE hInstance, HWND hOwner, XID xID);
	CXWindow(HINSTANCE hInstance, HWND hOwner, XID xID, WNDPROC WndProc);
	~CXWindow();
	virtual WNDCLASSEX CreateBasicClass(tstring &szClassName);

private:
	void Init();

protected:
	virtual bool CreateXWindow();

public:
	virtual CXWindow* GetOwnerWindow();
	virtual HWND GetOwner();
	virtual HINSTANCE GetInstance();
	virtual HWND GetHandle();
	virtual WNDPROC GetWndProc();
	virtual XID GetID();
	virtual COLORREF GetBackgroundColor();
	virtual RECT GetRect();
	virtual UINT GetWidth();
	virtual UINT GetHeight();
	virtual HICON GetIcon();
	virtual HICON GetIconSm();
	virtual WINDOWPOS GetPos();
	virtual DWORD GetStyle();
	virtual RECT & GetWndRect();

	virtual void SetOwnerWindow(CXWindow* pWindow);
	virtual void SetBgColor(COLORREF clColor);
	virtual void SetStyle(DWORD dwStyle);
	virtual void SetClass(tstring szClass);
	virtual void SetText(tstring szText);
	virtual void SetPos(int x, int y);
	virtual void SetPos(WINDOWPOS wpPos);
	virtual void SetRect(RECT rcRect);
	virtual void SetWidth(UINT uWidth);
	virtual void SetHeight(UINT uHeight);
	virtual void SetBrush(HBRUSH hBrush);

protected:
	CXWindow*	pOwnerWindow;
	HINSTANCE	hInstance;
	HWND		hOwner;
	HWND		hWnd;
	WNDPROC		WndProc;
	XID			xID;
	HBRUSH		hBgr;
	COLORREF	clBgr;
	RECT		rcRect;
	RECT		rcWindow;
	UINT		uWidth;
	UINT		uHeight;
	tstring		szClass;
	tstring		szText;
	tstring		szMenu;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	WINDOWPOS	wpPos;
	HICON		hIcon;
	HICON		hIconSm;
};

