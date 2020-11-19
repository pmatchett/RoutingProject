// RoutingProject.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CommCtrl.h"
#include "RoutingProject.h"
#include "RoutingMap.h"
#include "StaticRouter.h"
#include <string>
#include <vector>

#define MAX_LOADSTRING 100
#define MAPBUTTONID 0x8801
#define ROUTEBUTTONID 0x8802

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

RoutingMap mainMap(25, 25);         //TODO: figure out how to create this in main but pass it to WndProc without a global
StaticRouter mainRouter(&mainMap);  //TODO: figure out how to create this in main but pass it to WndProc without a global
HWND obsSlider;                     //TODO: figure out better way of passing the slider id between functions

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    //generating the map
    mainMap.generateMap();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROUTINGPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROUTINGPROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROUTINGPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROUTINGPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 1000, 750, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //creating the generate map button
   HWND mapButton = CreateWindowEx(
       0,
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"Generate Map",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       10,         // x position 
       10,         // y position 
       200,        // Button width
       50,        // Button height
       hWnd,     // Parent window
       (HMENU) MAPBUTTONID,       // No menu.
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);      // Pointer not needed.

   //creating the optimize route button
   HWND routeButton = CreateWindow(
       L"BUTTON",  // Predefined class; Unicode assumed 
       L"Determine Route",      // Button text 
       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
       400,         // x position 
       10,         // y position 
       200,        // Button width
       50,        // Button height
       hWnd,     // Parent window
       (HMENU)ROUTEBUTTONID,       // No menu. (id of the button)
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);      // Pointer not needed.


   //TODO set up a text box, ideally with up-down controls to enter the percentage of obstacles desired (maybe use a slider)
   //The text box where the user can input the percentage of squares that should be an obstacle
   /*HWND percentObsWindow = CreateWindow(
       L"EDIT",
       NULL,
       WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | ES_NUMBER,
       10,
       70,
       100,
       23,
       hWnd,
       NULL, //might need to use this to give it an id
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);*/

   //trying to make a slider
   double maxSlide = 100;
   double minSlide = 0;
   double tickInterval = 0.1;
   obsSlider = CreateWindow(
       TRACKBAR_CLASS,
       L"Amount Of Obstacles",
       WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
       10,80,200,30,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   SendMessage(obsSlider, TBM_SETRANGE, (WPARAM)true, (LPARAM)MAKELONG(minSlide, maxSlide)); // setting the max/min values of the slider
   SendMessage(obsSlider, TBM_SETTICFREQ, (WPARAM)10, 0); //Setting the slider to have tics every 10 units
   SendMessage(obsSlider, TBM_SETPOS, true, 25); //setting the default value to 25 percent

   HWND sliderLabel = CreateWindow(
       L"STATIC",
       L"Amount Of Obstacles:",
       WS_CHILD | WS_VISIBLE | SS_LEFT,
       10, 65, 150, 15,
       hWnd,
       NULL,
       (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
       NULL);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int sliderPosition;
            int testReturnValue;
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            //using HMENU id for buttons seems to overwrite BN_CLICKED message for it's own identifier, 
            //not sure if this is the best way to keep things consistent (could mmake theHwnd of buttons global but that seems bad
            //TODO: figure out best method to do this
            
            /*case BN_CLICKED:
                //TODO: need to find the button's identifier to make sure I can have multiple on the screen
                switch (wmId) {
                    case MAPBUTTONID:
                        OutputDebugString(_T("The button was clicked\n"));
                        mainMap.generateMap();
                        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                        break;
                    default:
                        OutputDebugString(_T("Unknown button clicked\n"));
                }*/

            case MAPBUTTONID:
                OutputDebugString(_T("The map button was clicked\n"));
                sliderPosition = SendMessage(obsSlider, TBM_GETPOS, 0, 0); //getting the positions of the slider to determine how many obstacles
                mainMap.generateMap((double)sliderPosition/100);
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
                break;
            case ROUTEBUTTONID:
                OutputDebugString(_T("The route button was clicked\n"));
                mainRouter.setEnd(mainMap.getEnd());
                mainRouter.setStart(mainMap.getStart());
                testReturnValue = mainRouter.optimizePath();
                if (testReturnValue == 0) {
                    OutputDebugString(_T("A path was found\n"));
                }
                else if (testReturnValue == 1) {
                    OutputDebugString(_T("No path could be found\n"));
                }
                break;
                
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }

        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            //adding the labels to the slider (might be a better place to put this)
            HPEN pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
            SelectObject(hdc, pen);
            HBRUSH redBrush = CreateSolidBrush(RGB(255,0,0));
            HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
            HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
            HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
            //TCHAR testText[] = _T("this is test of hdc");
            //TextOut(hdc, 100, 100, testText, _tcslen(testText));
            //drawing the map to the gui
            
            //TODO: work on dynamically moving the map/buttons based off size of the map
            for (int i = 0; i < mainMap.getX(); i++) {
                for (int j = 0; j < mainMap.getY(); j++) {
                    int status = mainMap.getPointStatus(i, j);
                    //changing the brush colour based off point status
                    if (status == FREE) {
                        SelectObject(hdc, whiteBrush);
                    }
                    else if (status == OBSTACLE) {
                        SelectObject(hdc, redBrush);
                    }
                    else if (status == START) {
                        SelectObject(hdc, greenBrush);
                    }
                    else if (status == END) {
                        SelectObject(hdc, yellowBrush);
                    }
                    //drawing the squares
                    Rectangle(hdc,10 + (10 * i), 130 + (10 * j), 20 + (10 * i), 140 + (10 * j));
                }
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
