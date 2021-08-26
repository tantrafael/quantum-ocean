#include <windows.h>

#include "Window.h"
#include "Game.h"


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
Window *g_pWindow = NULL;
Game   *g_pGame   = NULL;


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_CREATE:
		{
			SetTimer( hWnd, 1, 25, 0 );
			break;
		}

        case WM_TIMER:
		{
			g_pGame->update();
			break;
		}

		case WM_DESTROY:
		{
            PostQuitMessage( 0 );
			break;
		}
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "Class", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
	int width  = 640;
	int height = 480;
	HWND hWnd = CreateWindow( "Class", "Quantana Mera",
                              WS_OVERLAPPEDWINDOW, 100, 100, width, height,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

	// Show the window
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	// Initialize Game
	g_pWindow = new Window( hInst, hWnd, width, height );
	g_pGame   = new Game( g_pWindow );

	// Enter the message loop
	MSG msg; 
	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

/*
	bool run = true;
	while(run)
	{
		MSG msg; 
		while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if(msg.message == WM_QUIT)
				run = false;
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if(!run)
			break;

		g_game->update();
	}
*/

	delete g_pGame;
	delete g_pWindow;
	
    // Exit the app
    UnregisterClass( "Class", wc.hInstance );

	return 0;
}
