#pragma once
#include "Renderer.h"
#include "Keyboard.h"
#include "Mouse.h"


const bool FULL_SCREEN = false;

class D2DWindow
{
	
	friend class Game;
	HRESULT Initialize();
	static std::size_t m_screenWidth;
	static std::size_t m_screenHeight;
	static HWND m_hwnd;
	static Keyboard kbd;
	static Mouse mouse;

public:
	D2DWindow(const std::size_t& width,const std::size_t& height);
	~D2DWindow();
	
	
	// Process and dispatch messages
	bool RunMessageLoop();
	static std::size_t ScreenWidth();
	static std::size_t ScreenHeight();
	static HWND WindowHandle();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

