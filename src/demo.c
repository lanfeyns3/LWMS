#include "window.h"

int main() {
    struct LWMSWindow* ret = LWMS_createWindow("lol");

    while (ret->active == 1)
    {
        LWMS_pollMessage(ret);
    }
}
