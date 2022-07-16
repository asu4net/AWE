#pragma once
#include "AWEpch.h"

namespace AWE
{
	class AWE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Start();
	};

	//This must be implemented in the user side.
	Application* CreateApplication();
}