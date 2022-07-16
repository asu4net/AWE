#include "AWE.h"

using namespace AWE;

struct GameArgs {};

class Game final : public Application
{
	Event<GameArgs> OnGameStart;

public:

	void SayHello(GameArgs t_args) { LOG_INFO("Hello AWE! {}", 2); }

	virtual void Start() override
	{	
		Application::Start();
		auto listener = OnGameStart.ADD_LISTENER(Game, SayHello);
		//OnGameStart.RemoveListener(listener);
		OnGameStart.Invoke({});
	}
};

AWE::Application* AWE::CreateApplication() { return new Game(); }

