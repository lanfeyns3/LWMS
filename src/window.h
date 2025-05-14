#include <stdio.h>
#include "backends/win32window.h"

struct LWMSWindow
{
#ifdef _WIN32
	HWND* instance;
	MSG msg;
#endif // _WIN32
	int active;
};

void LWMS_NextWindow_Icon(const char* fileLocation);

void LWMS_pollMessage(struct LWMSWindow* window);

struct LWMSWindow* LWMS_createWindow(const char* name);