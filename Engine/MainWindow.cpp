/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	MainWindow.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Resource.h"
#include "Graphics.h"
#include "ChiliException.h"
#include "Game.h"
#include <assert.h>

MainWindow::MainWindow( HINSTANCE hInst,wchar_t * pArgs )
	:
	args( pArgs ),
	hInst( hInst )
{
	// register window class
	WNDCLASSEX wc = { sizeof( WNDCLASSEX ),CS_CLASSDC,_HandleMsgSetup,0,0,
		hInst,nullptr,nullptr,nullptr,nullptr,
		wndClassName,nullptr };
	wc.hIconSm = (HICON)LoadImage( hInst,MAKEINTRESOURCE( IDI_APPICON ),IMAGE_ICON,16,16,0 );
	wc.hIcon = (HICON)LoadImage( hInst,MAKEINTRESOURCE( IDI_APPICON ),IMAGE_ICON,32,32,0 );
	wc.hCursor = LoadCursor( nullptr,IDC_ARROW );
	RegisterClassEx( &wc );

	// create window & get hWnd
	RECT wr;
	wr.left = (GetSystemMetrics(SM_CXSCREEN) - Graphics::ScreenWidth) / 2;
	wr.right = Graphics::ScreenWidth + wr.left;
	wr.top = (GetSystemMetrics(SM_CYSCREEN) - Graphics::ScreenHeight) / 2;
	wr.bottom = Graphics::ScreenHeight + wr.top;
	AdjustWindowRect( &wr,WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,FALSE );
	hWnd = CreateWindow( wndClassName,L"Chili DirectX Framework",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left,wr.top,wr.right - wr.left,wr.bottom - wr.top,
		nullptr,nullptr,hInst,this );

	// throw exception if something went terribly wrong
	if( hWnd == nullptr )
	{
		throw Exception( _CRT_WIDE( __FILE__ ),__LINE__,
			L"Failed to get valid window handle." );
	}

	// show and update
	ShowWindow( hWnd,SW_SHOWDEFAULT );
	UpdateWindow( hWnd );
}

MainWindow::~MainWindow()
{
	// unregister window class
	UnregisterClass( wndClassName,hInst );
}

bool MainWindow::IsActive() const
{
	return GetActiveWindow() == hWnd;
}

bool MainWindow::IsMinimized() const
{
	return IsIconic( hWnd ) != 0;
}

void MainWindow::ShowMessageBox( const std::wstring& title,const std::wstring& message ) const
{
	MessageBox( hWnd,message.c_str(),title.c_str(),MB_OK );
}

bool MainWindow::ProcessMessage()
{
	MSG msg;
	while( PeekMessage( &msg,nullptr,0,0,PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		if( msg.message == WM_QUIT )
		{
			return false;
		}

		if (kbd.KeyIsPressed(VK_ESCAPE))
			PostQuitMessage(0);
	}
	return true;
}

LRESULT WINAPI MainWindow::_HandleMsgSetup( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if( msg == WM_NCCREATE )
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>( lParam );
		MainWindow* const pWnd = reinterpret_cast<MainWindow*>( pCreate->lpCreateParams );
		// sanity check
		assert( pWnd != nullptr );
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr( hWnd,GWLP_USERDATA,reinterpret_cast<LONG_PTR>( pWnd ) );
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr( hWnd,GWLP_WNDPROC,reinterpret_cast<LONG_PTR>( &MainWindow::_HandleMsgThunk ) );
		// forward message to window class handler
		return pWnd->HandleMsg( hWnd,msg,wParam,lParam );
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc( hWnd,msg,wParam,lParam );
}

LRESULT WINAPI MainWindow::_HandleMsgThunk( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
{
	// retrieve ptr to window class
	MainWindow* const pWnd = reinterpret_cast<MainWindow*>( GetWindowLongPtr( hWnd,GWLP_USERDATA ) );
	// forward message to window class handler
	return pWnd->HandleMsg( hWnd,msg,wParam,lParam );
}

LRESULT MainWindow::HandleMsg( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

		// ************ KEYBOARD MESSAGES ************ //
	case WM_KEYDOWN:
		if( !(lParam & 0x40000000) || kbd.AutorepeatIsEnabled() ) // no thank you on the autorepeat
		{
			kbd.OnKeyPressed( static_cast<unsigned char>(wParam) );
		}
		break;
	case WM_KEYUP:
		kbd.OnKeyReleased( static_cast<unsigned char>(wParam) );
		break;
	case WM_CHAR:
		kbd.OnChar( static_cast<unsigned char>(wParam) );
		break;
		// ************ END KEYBOARD MESSAGES ************ //

		// ************ MOUSE MESSAGES ************ //
	case WM_MOUSEMOVE:
	{
		POINTS pts = MAKEPOINTS(lParam);
		if( pts.x > 0 && pts.x < Graphics::ScreenWidth && pts.y > 0 && pts.y < Graphics::ScreenHeight )
		{
			mouse.OnMouseMove(pts.x, pts.y );
			if( !mouse.IsInWindow() )
			{
				SetCapture( hWnd );
				mouse.OnMouseEnter();
			}
		}
		else
		{
			if( wParam & (MK_LBUTTON | MK_RBUTTON) )
			{
				pts.x = std::max( short(0), pts.x );
				pts.x = std::min( short( Graphics::ScreenWidth  - 1), pts.x );
				pts.y = std::max( short(0), pts.y );
				pts.y = std::min( short( Graphics::ScreenHeight  - 1), pts.y );
				mouse.OnMouseMove(pts.x, pts.y );
			}
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
				mouse.OnLeftReleased(pts.x, pts.y );
				mouse.OnRightReleased(pts.x, pts.y );
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		POINTS pts = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pts.x, pts.y );
		break;
	}
	case WM_RBUTTONDOWN:
	{
		POINTS pts = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pts.x, pts.y );
		break;
	}
	case WM_LBUTTONUP:
	{
		POINTS pts = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pts.x, pts.y );
		break;
	}
	case WM_RBUTTONUP:
	{
		POINTS pts = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pts.x, pts.y );
		break;
	}
	case WM_MOUSEWHEEL:
	{
		POINTS pts = MAKEPOINTS(lParam);
		if( GET_WHEEL_DELTA_WPARAM( wParam ) > 0 )
		{
			mouse.OnWheelUp( pts.x,pts.y );
		}
		else if( GET_WHEEL_DELTA_WPARAM( wParam ) < 0 )
		{
			mouse.OnWheelDown(pts.x, pts.y );
		}
		break;
	}
	// ************ END MOUSE MESSAGES ************ //
	}

	return DefWindowProc( hWnd,msg,wParam,lParam );
}