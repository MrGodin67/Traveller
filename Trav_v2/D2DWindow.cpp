#include "stdafx.h"
#include "D2DWindow.h"


Keyboard D2DWindow::kbd;
Mouse D2DWindow::mouse;
std::size_t D2DWindow::m_screenWidth;
std::size_t D2DWindow::m_screenHeight;
HWND D2DWindow::m_hwnd;

D2DWindow::D2DWindow(const std::size_t& width, const std::size_t& height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	Initialize();
}


D2DWindow::~D2DWindow()
{
}

HRESULT D2DWindow::Initialize()
{
	
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	std::size_t posX, posY;
	HRESULT hr = S_OK;

	
	HINSTANCE m_hinstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"D2DWindow";
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	int screenWidth2 = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight2 = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
		
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_screenHeight) / 2;
	}


	RECT wr = { (long)posX,(long)posY,(long)posX+(long)m_screenWidth,(long)posY+(long)m_screenHeight };
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	m_hwnd = CreateWindow(L"D2DWindow", L"Test",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, m_hinstance, this);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);


	ShowCursor(true);

	return hr;
}

bool D2DWindow::RunMessageLoop()
{
	MSG msg = {};
	bool OK = true;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			OK = false;
		}
	}
	return OK;
}
std::size_t D2DWindow::ScreenWidth()
{
	return m_screenWidth;
}
std::size_t D2DWindow::ScreenHeight()
{
	return m_screenHeight;
}
HWND D2DWindow::WindowHandle()
{
	return m_hwnd;
}
LRESULT D2DWindow::WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (!(lparam & 0x40000000) || kbd.AutorepeatIsEnabled()) // no thank you on the autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wparam));
		}
		break;
	case WM_KEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wparam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wparam));
		break;

	case WM_MOUSEMOVE:
	{
		POINTS pt = MAKEPOINTS(lparam);
		if (pt.x > 0 && pt.x < m_screenWidth && pt.y > 0 && pt.y < m_screenHeight)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(m_hwnd);
				mouse.OnMouseEnter();
			}
		}
		else
		{
			if (wparam & (MK_LBUTTON | MK_RBUTTON))
			{
				pt.x = std::max<short>(short(0), pt.x);
				pt.x = std::min<short>(short(m_screenWidth - 1), pt.x);
				pt.y = std::max<short>(short(0), pt.y);
				pt.y = std::min<short>(short(m_screenHeight - 1), pt.y);
				mouse.OnMouseMove(pt.x, pt.y);
			}
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
				//mouse.OnLeftReleased(pt.x, pt.y);
				//mouse.OnRightReleased(pt.x, pt.y);
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lparam);
		mouse.OnRightReleased(pt.x, pt.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lparam);
		if (GET_WHEEL_DELTA_WPARAM(wparam) > 0)
		{
			mouse.OnWheelUp(pt.x, pt.y);
		}
		else if (GET_WHEEL_DELTA_WPARAM(wparam) < 0)
		{
			mouse.OnWheelDown(pt.x, pt.y);
		}
		break;
	}

	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}
