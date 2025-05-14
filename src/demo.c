#include "window.h"

int main() {
    struct LWMSWindow* window = LWMS_createWindow("SP[Alpha]");
    while (window->active == 1)
    {
        LWMS_pollMessage(window);
    }
    return 0;
}
