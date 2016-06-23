//***********************************************************************************************
//***********************************************************************************************
//							Componet Framework of Engine 702
//
//									General Utility Code
//
//*******************************  All Rights Reserved  *****************************************
//***********************************************************************************************
#ifndef UTIL702_H
#define UTIL702_H

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#endif



#include <d3dx11.h>
#include <string>
#include <sstream>
#include "d3dx11Effect.h"
#include <xnamath.h>
#include <dxerr.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>


#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)												\
	{															\
		HRESULT hr = x;											\
		if (FAILED(hr))											\
		{														\
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true);	\
		}														\
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif

#define ReleaseCOM(x)			\
{								\
	if (x)						\
	{							\
		x->Release();			\
		x = 0;					\
	}							\
}

#define SafeDelete(x) { delete x; x = 0; }


namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White     = {1.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Black     = {0.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Red       = {1.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Green     = {0.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Blue      = {0.0f, 0.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Yellow    = {1.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Cyan      = {0.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Magenta   = {1.0f, 0.0f, 1.0f, 1.0f};

	XMGLOBALCONST XMVECTORF32 Silver    = {0.75f, 0.75f, 0.75f, 1.0f};
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = {0.69f, 0.77f, 0.87f, 1.0f};
}


#endif // UTIL702_H

//***********************************************************************************************
//***********************************  Questions  ***********************************************
//1. 
//2.
//3.
//***********************************************************************************************
//***********************************************************************************************