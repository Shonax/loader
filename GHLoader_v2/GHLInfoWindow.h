#pragma once
#include "XGui\XDialog.h"
#include "XGui\XControls.h"
#define INFOWND_W 300
#define INFOWND_H 300

#define IDC_INFOEDIT 0x8000

class GHLInfoWindow : public CXDialog
{
public:
	GHLInfoWindow(CXWindow * pOwner);
	GHLInfoWindow(CXWindow * pOwner, int x, int y);
	~GHLInfoWindow();
	virtual void Show();
private:
	void GetInfoText();
	void CreateControls();

private:
	tstring szInfo;
};

