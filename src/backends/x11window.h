#ifdef __linux__
#include <X11/Xlib.h>

struct createWindowReturn
{
    Display* display;
    Window window;
    XEvent event;
    int screen;
};

struct createWindowReturn LWMS_X11_create();

#endif