#include <windows.h>
#include <string>

#define ID_ADD 1
#define ID_REMOVE 2
#define ID_INPUT 3
#define ID_LIST 4

HWND hInput, hList;

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            CreateWindow("STATIC", "Enter Task:",
                WS_VISIBLE | WS_CHILD,
                20, 20, 100, 25,
                hwnd, NULL, NULL, NULL);

            hInput = CreateWindow("EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                120, 20, 200, 25,
                hwnd, (HMENU)ID_INPUT, NULL, NULL);

            CreateWindow("BUTTON", "Add Task",
                WS_VISIBLE | WS_CHILD,
                330, 20, 100, 25,
                hwnd, (HMENU)ID_ADD, NULL, NULL);

            CreateWindow("BUTTON", "Remove Selected",
                WS_VISIBLE | WS_CHILD,
                330, 60, 120, 25,
                hwnd, (HMENU)ID_REMOVE, NULL, NULL);

            hList = CreateWindow("LISTBOX", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
                20, 60, 300, 200,
                hwnd, (HMENU)ID_LIST, NULL, NULL);
        }
        break;

        case WM_COMMAND:
        {
            if(LOWORD(wp) == ID_ADD)
            {
                char text[256];
                GetWindowText(hInput, text, 256);

                if(strlen(text) > 0)
                {
                    SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)text);
                    SetWindowText(hInput, "");
                    MessageBeep(MB_OK);
                }
            }

            if(LOWORD(wp) == ID_REMOVE)
            {
                int sel = SendMessage(hList, LB_GETCURSEL, 0, 0);
                if(sel != LB_ERR)
                {
                    SendMessage(hList, LB_DELETESTRING, sel, 0);
                    MessageBeep(MB_ICONHAND);
                }
            }
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// Entry point
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "TodoApp";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "TodoApp",
        "To-Do List (GUI Version)",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        300, 200, 500, 350,
        NULL, NULL, hInst, NULL);

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

