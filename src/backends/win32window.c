#ifdef _WIN32
#define STB_IMAGE_IMPLEMENTATION
#include "win32window.h"

HICON hIcon;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect); // get the full window client area

        // Fill the whole client area or draw your content accordingly
        FillRect(hdc, &clientRect, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



void LWMS_Win32_NextWindow_Icon(const char* fileLocation)
{

    int width, height, channels;
    stbi_uc* pixels = stbi_load(fileLocation, & width, & height, & channels, 4);

    for (int i = 0; i < width * height; ++i) {
        unsigned char* px = &pixels[i * 4];
        unsigned char r = px[0];
        px[0] = px[2];
        px[2] = r;
    }

    BITMAPV5HEADER bi = { 0 };
    bi.bV5Size = sizeof(bi);
    bi.bV5Width = width;
    bi.bV5Height = -height;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000;
    bi.bV5GreenMask = 0x0000FF00;
    bi.bV5BlueMask = 0x000000FF;
    bi.bV5AlphaMask = 0xFF000000;

    void* dibData = NULL;
    HDC hdc = GetDC(NULL);
    HBITMAP colorBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &dibData, NULL, 0);
    ReleaseDC(NULL, hdc);

    if (!colorBitmap) {
        stbi_image_free(pixels);
        return NULL;
    }

    memcpy(dibData, pixels, width * height * 4);
    stbi_image_free(pixels);

    ICONINFO ii = { 0 };
    ii.fIcon = TRUE;
    ii.hbmColor = colorBitmap;
    ii.hbmMask = colorBitmap;

    hIcon = CreateIconIndirect(&ii);

    DeleteObject(colorBitmap);
}

int LWMS_Win32_poll(MSG msg)
{
    int val = GetMessage(&msg, NULL, 0, 0);
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    return val;
}

struct createWindowReturn LWMS_Win32_create(const char* name)
{
    const wchar_t* CLASS_NAME = malloc(sizeof(wchar_t) * 10);

    mbtowc(CLASS_NAME, name, sizeof(char) * strlen(name));

    struct createWindowReturn ret = { (HWND*)malloc(sizeof(HWND)), NULL };

    WNDCLASS wc = { 0 };
    HINSTANCE hInstance = GetModuleHandle(NULL);

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    if (hIcon)
    {
        wc.hIcon = hIcon;
        hIcon = NULL;
    }

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Failed to register window class", "Error", MB_ICONERROR);
        return;
    }

    *ret.window = CreateWindowEx(
        0,
        CLASS_NAME,
        name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (*ret.window == NULL) {
        MessageBox(NULL, "Failed to create window!", "Error", MB_ICONERROR);
        return;
    }

    ShowWindow(*ret.window, SW_SHOW);
    UpdateWindow(*ret.window);

    GetMessage(&ret.msg, NULL, 0, 0);
    TranslateMessage(&ret.msg);
    DispatchMessage(&ret.msg);

	return ret;
}
#endif