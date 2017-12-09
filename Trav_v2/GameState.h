#pragma once
#include "stdafx.h"

enum  class  GameState : std::size_t
{
	running,
	paused,
	exit,
	menu,
	start
};