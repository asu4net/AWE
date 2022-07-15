#include "AWEpch.h"
#include "Application.h"
#include "AWE/Log/Log.h"

namespace AWE
{
	Application::Application()
	{
		Log::Create();
		AWE_LOG_TRACE("Application created.");
	}
	Application::~Application()
	{
		AWE_LOG_TRACE("Application destroyed.");
	}
	void Application::Start()
	{
		AWE_LOG_TRACE("Application started.");
	}
}