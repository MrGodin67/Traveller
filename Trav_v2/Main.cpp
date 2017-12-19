#include "stdafx.h"
#include "D2DWindow.h"
#include "Game.h"
#include "SimpleTimer.h"

static const std::size_t scrnW = 800;
static const std::size_t scrnH = 600;
int WINAPI WinMain(	HINSTANCE ,	HINSTANCE,	LPSTR,	int )
{
	
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	
	if (SUCCEEDED(CoInitialize(NULL)))
	{
		
	
		// create in this order
		D2DWindow wind(scrnW, scrnH);
		Game app(wind);
		SimpleTimer timer;
		timer.Reset();
		
		bool ok = true;
		while (ok)
		{
			timer.Update();
	
			if ((ok = wind.RunMessageLoop()))
				 ok = app.Play(timer);
		}
		  CoUninitialize();
	}
}