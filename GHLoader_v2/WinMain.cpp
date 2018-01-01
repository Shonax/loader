#include "GHLoader.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	GHLoader loader(hInstance);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		if (!loader.IsDlgMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}