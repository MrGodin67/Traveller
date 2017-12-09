#pragma once
#define NOMINMAX
#include <Windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>
#include <array>
#include <dwrite.h>

#include "randomizer.h"
#include "RangeBased.h"
#include "D2DStuff.h"
#pragma comment(lib,"d2d1.lib")

template<typename T>
static T Sign(T val)
{
	if (val == (T)0)
		return (T)0;
	return std::signbit((float)val) ? (T)-1 : (T)1;
}
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

template<class Interface>
inline void SafeDelete(Interface **ppInterfaceToFree)
{
	if (*ppInterfaceToFree != NULL)
	{ 
		delete (*ppInterfaceToFree);

		(*ppInterfaceToFree) = NULL;
	}
}
template<class Interface>
inline void SafeDeleteArray(Interface **ppInterfaceToFree)
{
	if (*ppInterfaceToFree != NULL)
	{
		delete [] (*ppInterfaceToFree);

		(*ppInterfaceToFree) = NULL;
	}
}


inline static bool LittleEndian()
{
	int i = 1;
	// get address of i
	char * c = (char*)&i;
	// if it reads the lower bit first ie: i = 1
	return ((int)*c == i);
}

template <typename Type, typename... TArgs>
std::unique_ptr<Type> MakeUnique(TArgs&&... mArgs)
{
	Type* obj(new Type(std::forward<TArgs>(mArgs)...));
	std::unique_ptr<Type> uPtr{ obj };
	return std::move(uPtr);
	
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

using D2DRectF = D2D1_RECT_F;
using D2DMatrix = D2D1_MATRIX_3X2_F;
using D2DPointF = D2D1_POINT_2F;
using D2DSizeF = D2D1_SIZE_F;

