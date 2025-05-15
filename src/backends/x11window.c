#ifdef __linux__
#include "x11window.h"

struct createWindowReturn LWMS_X11_create()
{
   struct createWindowReturn ret;
   ret.display = XOpenDisplay(NULL);
   ret.screen = DefaultScreen(ret.display);
   
   ret.window = XCreateSimpleWindow(ret.display,XRootWindow(ret.display,ret.screen),50,50,800,600,20,BlackPixel(ret.display,ret.screen),WhitePixel(ret.display,ret.screen));

   XSelectInput(ret.display,ret.window,ExposureMask);
   XMapWindow(ret.display,ret.window);

   return ret;
}
#endif