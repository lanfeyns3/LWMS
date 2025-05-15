#include <stdio.h>
#include <stdlib.h>
#include "backends/win32window.h"
#include "backends/x11window.h"

struct LWMSWindow
{
#ifdef _WIN32
	HWND* instance;
	MSG msg;
#endif // _WIN32
#ifdef __linux__
	Display* display;
	Window window;
	XEvent event;
	int screen;
#endif
	int active;
};

void LWMS_NextWindow_Icon(const char* fileLocation);

void LWMS_pollMessage(struct LWMSWindow* window);

struct LWMSWindow* LWMS_createWindow(const char* name);