#ifdef _WIN32
#ifndef win32Window
	#define win32Window
	#include <Windows.h>
	#include <stb_image.h>
	
	struct createWindowReturn
	{
		HWND* window;
		MSG msg;
	};
	
	void LWMS_Win32_NextWindow_Icon(const char* fileLocation);
	
	int LWMS_Win32_poll(MSG msg);
	struct createWindowReturn LWMS_Win32_create(const char* name);
#endif // !win32Window

#endif // _WIN32
