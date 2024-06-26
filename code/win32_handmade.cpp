#include <windows.h>

LRESULT MainWindowCallback(HWND WindowHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    LRESULT Result = 0;
    switch (Message)
    {
    // Window created
    case WM_CREATE:
    {
        OutputDebugString("WM_CREATE\n");
        break;
    }
    // Size changed
    case WM_SIZE:
    {
        OutputDebugString("WM_SIZE\n");
        break;
    }
    // Window destroyed by OS
    case WM_DESTROY:
    {
        OutputDebugString("WM_DESTROY\n");
        break;
    }
    // User closed the windows
    case WM_CLOSE:
    {        
        OutputDebugString("WM_CLOSE\n");
        break;
    }
    // User focus the windows
    case WM_ACTIVATEAPP:
    {
        OutputDebugString("WM_ACTIVATEAPP\n");
        break;
    }
    case WM_PAINT:
    {
        OutputDebugString("WM_PAINT\n");

        PAINTSTRUCT paint;
        HDC deviceContext = BeginPaint(WindowHandle, &paint);

        int X = paint.rcPaint.left;
        int Y = paint.rcPaint.top;
        int Width = paint.rcPaint.right - paint.rcPaint.left;
        int Height = paint.rcPaint.bottom - paint.rcPaint.top;
        static DWORD Operation = WHITENESS;


        PatBlt(deviceContext, X, Y, Width, Height, Operation);

        if (Operation == WHITENESS)
        {
            Operation = BLACKNESS;
        }
        else 
        {
            Operation = WHITENESS;
        }

        EndPaint(WindowHandle, &paint);
        break;
    }
    default:
    {
        // Let default window procedure to handle other messages
        Result = DefWindowProc(WindowHandle, Message, wParam, lParam);
    }
    }
    return Result;
}

int WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int ShowCmd)
{
    WNDCLASS windowClass{};
    windowClass.style = CS_OWNDC |    // Allocates a unique device context for each window in the class.
                        CS_HREDRAW |  // Redraw window if the widht changed
                        CS_VREDRAW;   // Redraw window if the height changed
    windowClass.lpfnWndProc = MainWindowCallback;
    windowClass.hInstance = Instance;
    windowClass.lpszClassName = "HandmadeHeroWindowClass";

    if (RegisterClass(&windowClass))
    {
        HWND WindowHandle = CreateWindowExA(0,                                 // dwExStyle
                                            windowClass.lpszClassName,         // lpClassName
                                            "Handmade hero",                   // lpWindowName
                                            WS_OVERLAPPEDWINDOW | WS_VISIBLE,  // dwStyle
                                            CW_USEDEFAULT,                     // X
                                            CW_USEDEFAULT,                     // Y
                                            CW_USEDEFAULT,                     // nWidth
                                            CW_USEDEFAULT,                     // nHeight
                                            0,                                 // hWndParent,
                                            0,                                 // hMenu,
                                            Instance,                          // hInstance
                                            0                                  // lpParam
        );

        if (WindowHandle)
        {
            MSG Message;

            for (;;)
            {
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if (MessageResult <= 0)
                {
                    break;
                }

                TranslateMessage(&Message);
                DispatchMessage(&Message);
            }
        }
        // Error handling
        else
        {
            // TODO: Logging
        }
    }
    // Error handling
    else
    {
        // TODO: Logging
    }

    return 0;
}
