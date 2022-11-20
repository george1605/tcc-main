#include <windows.h>
#include <stdio.h>
#define main() WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)

static HWND _mainWin = NULL;
static HDC _mainDC = NULL;
int initwindow(int width, int height, const char* name)
{
    _mainWin = CreateWindowExA(0, "WINDOW", name, WS_BORDER | WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, NULL, NULL);
    ShowWindow(_mainWin, SW_NORMAL);
    _mainDC = GetWindowDC(_mainWin);
}

void initclass()
{
    const wchar_t CLASS_NAME[] = L"WINDOW";

    WNDCLASSA wc;
    ZeroMemory(&wc, sizeof wc);

    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = 0;
    wc.hbrBackground = CreateSolidBrush(RGB(180, 180, 180));
    wc.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
    wc.lpszClassName = CLASS_NAME;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    RegisterClass(&wc);
}

void outtext(char* text, int x, int y)
{
    TextOutA(_mainDC, x, y, text, strlen(text));
}

void putpixel(int x, int y, int color)
{
    SetPixel(_mainDC, x, y, (COLORREF)color);
}

void drawline(int x1, int y1, int x2, int y2)
{
    MoveToEx(_mainDC, x1, y1, NULL);
    LineTo(_mainDC, x2, y2);
}

void* swapbuf(void* buffer)
{
    if(buffer == NULL)
        MessageBoxA(NULL, "Buffer passed to swapbuf cannot be NULL.", "Error", MB_ICONERROR);
    HDC temp = _mainDC;
    _mainDC = buffer;
    return (void*)temp;
}

void* allocbuf()
{
    return CreateCompatibleDC(_mainDC);
}

typedef void(*event_handler)(MSG);
void msgloopx(event_handler p)
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        if(!p)
            DispatchMessage(&msg);
        else
            p(msg);
    }
}
#define _quit(code) PostQuitMessage(code)
#define msgloop() msgloopx(NULL)