#pragma once
#include "directX.h"
#define VC_EXTRALEAN
HINSTANCE g_hInst;				// holds the instance for this app
HWND wndHandle;					// global window handle
bool g_bWindowed;				//boolean for windowed or full screen mode
#define WINDOW_TITLE "Direct X - Week 2 iLab"

DirectX graphics;
bool playerQuit = false;


////////////////////////////////////////////// forward declarations
bool    initWindow(void);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	g_hInst = hInstance;
	g_bWindowed = true;

	graphics = DirectX();

	// call our function to init and create our window
	if (!initWindow())
	{
		MessageBox(NULL, "Unable to create window", "ERROR", MB_OK);
		return 0;
	}

	if (!graphics.Init(wndHandle,g_hInst, true))
	{
		MessageBox(NULL, "Unable to init Direct3D", "ERROR", MB_OK);
		return 0;
	}

	// Main message loop:
	// Enter the message loop
    MSG msg; 
    ZeroMemory( &msg, sizeof(msg) );
	//g_DX.Init(wndHandle,g_hInst,g_bWindowed);
    while( msg.message!=WM_QUIT && !playerQuit )
    {
		// check for messages
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
			
        }
		// this is called when no messages are pending
		else
		{
			if(graphics.Update(&playerQuit) == true)
				break;
			graphics.Render();
		}
    }
	graphics.Shutdown();
	UnregisterClass(WINDOW_TITLE, g_hInst);


	// release and shutdown Direct3D
	//graphics.Shutdown();
	return (int) msg.wParam;
}

bool initWindow()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInst;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOWFRAME);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= WINDOW_TITLE;
	wcex.hIconSm		= 0;

	RegisterClassEx(&wcex);

	wndHandle = CreateWindow(
		WINDOW_TITLE, WINDOW_TITLE, 							// window class name and title
		g_bWindowed ? WS_OVERLAPPEDWINDOW | WS_VISIBLE:(WS_POPUP | WS_VISIBLE),// window style
		CW_USEDEFAULT, CW_USEDEFAULT, 
		SCREEN_WIDTH, SCREEN_HEIGHT, 
		NULL, NULL, 
		g_hInst, 
		NULL);

   ShowWindow(wndHandle, SW_SHOW);
   UpdateWindow(wndHandle);

   if (!wndHandle)
      return false;
   return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
