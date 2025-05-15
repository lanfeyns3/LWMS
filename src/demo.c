#include "window.h"

int main() {
    struct LWMSWindow* ret = LWMS_createWindow("lol");

    for (;;)
    {
        XNextEvent(ret->display,&ret->event);
    }
}
