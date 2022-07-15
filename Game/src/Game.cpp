#include "AWE.h"

using namespace AWE;

struct GameArgs {};

class Game : public Application
{
	Event<GameArgs> OnGameStart;

public:

	void SayHello(GameArgs args) { LOG("Hello AWE!"); }

	virtual void Start() override
	{
		auto listener = OnGameStart.ADD_LISTENER(Game, SayHello);
		OnGameStart.RemoveListener(listener);
		OnGameStart.Invoke({});
	}
};

AWE::Application* AWE::CreateApplication() { return new Game(); }

