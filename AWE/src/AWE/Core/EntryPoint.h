#pragma once

#include "AWEpch.h"
#include "Application.h"

#ifdef AWE_PLATFORM_WINDOWS

int main()
{
	auto app = AWE::CreateApplication();
	app->Start();
	delete app;
	
	return 0;
}

#endif
