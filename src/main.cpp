// Standards
#include <synchapi.h>
#include <windows.h>
#include <windef.h>

#define WM_TRAY (WM_APP + 1)
bool isClosing = false;
NOTIFYICONDATAA nid = {};

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {
    if (_msg == WM_TRAY && _lParam == WM_LBUTTONDOWN) {
        ShowWindow(_hwnd, SW_SHOW);
        SetForegroundWindow(_hwnd);
        return 0;
    }

    if (_msg == WM_CLOSE) {
        isClosing = true;
        PostQuitMessage(0);

        return 0;
    }

    return DefWindowProcW(_hwnd, _msg, _wParam, _lParam);
}

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE, LPSTR, int) {
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = _hInstance;
    wc.lpszClassName = L"Imposter in the system tray";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowA
    (
        "Imposter in the system tray", 
        "Imposter in the system tray", 
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        400, 
        200,
        nullptr, 
        nullptr, 
        _hInstance, 
        nullptr
    );

    if (!hwnd) 
    {
        return 0;
    }

    HICON icon = static_cast<HICON>(LoadImageA
    (
        NULL,
        "icon.ico",
        IMAGE_ICON,
        0,
        0,
        LR_LOADFROMFILE | LR_DEFAULTSIZE
    ));
  
    if (!icon)
    {
        return 0;
    }

    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uFlags = NIF_ICON | NIF_MESSAGE;
    nid.hIcon = icon;
    nid.uCallbackMessage = WM_TRAY;

    Shell_NotifyIconA(NIM_ADD, &nid);

    MSG msg = {};
    while (!isClosing && GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    Shell_NotifyIconA(NIM_DELETE, &nid);

    return 0;
}