#include "window.h"

void LWMS_NextWindow_Icon(const char* fileLocation)
{
#ifdef _WIN32
    LWMS_Win32_NextWindow_Icon(fileLocation);
#endif // _WIN32

}

void LWMS_pollMessage(struct LWMSWindow* window)
{
#ifdef _WIN32
    if (LWMS_Win32_poll(window->msg) == 0)
    {
        window->active = 0;
    }
#endif // _WIN32

}

struct LWMSWindow* LWMS_createWindow(const char* name)
{
#ifdef _WIN32
    struct createWindowReturn retWin = LWMS_Win32_create(name);
    struct LWMSWindow* newWindow = malloc(sizeof(struct LWMSWindow));
    
    newWindow->active = 1;
    newWindow->instance = retWin.window;
    newWindow->msg = retWin.msg;
    
    return newWindow;
#endif // _WIN32
}
