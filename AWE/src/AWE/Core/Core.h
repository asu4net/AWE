#pragma once

#ifdef AWE_PLATFORM_WINDOWS
#ifdef AWE_BUILD_DLL
#define AWE_API __declspec(dllexport)
#else
#define AWE_API __declspec(dllimport)
#endif
#else
#error AWE only supports Windows!
#endif