#include "GameLoop.h"

SDL_Keycode keypress;
System::Point2D<float> Position = { 800, 450 };
int timer = 0;
int alphaControl = 1;
int speed = 25;

bool bullet = false;
float bullteTrav = Position.Y;
int bullife = 25;

void GameLoop::Loop()
{
	while (m_bRunning)
	{
		SDL_Event sdlEvent; // Will hold the next event to be parsed

		while (m_bRunning)
		{
			// Events get called one at a time, so if multiple things happen in one frame, they get parsed individually through 'SDL_PollEvent'
			// The next event to parse gets stored into 'sdlEvent', and then passed to the 'EventHandler' class which will call it's appropriate function here
			// 'SDL_PollEvent' returns 0 when there are no more events to parse
			while (SDL_PollEvent(&sdlEvent))
			{
				// Calls the redefined event function for the EventHandler class
				// Refer to its header file and cpp for more information on what each inherited function is capable of
				// and its syntax
				OnEvent(sdlEvent);
			}
			Update();

			LateUpdate();

			Draw();

			Graphics::Flip(); // Required to update the window with all the newly drawn content
		}
	}
}



void GameLoop::Update()
{
	timer += 1;//Timmer

	

	switch (keypress)//Movement
	{
	case SDLK_DOWN:
		Position.Y += speed;
		break;

	case SDLK_UP:
		Position.Y -= speed;
		break;

	case SDLK_LEFT:
		Position.X -= speed;
		break;

	case SDLK_RIGHT:
		Position.X += speed;
		break;

	case SDLK_0:
		bullet = true;
		break;

	default:
		break;
	}

	if (bullet == true && bullife > 0)//Bullet life
	{
		bullife -= 1;
	}

	else
	{
		bullet = false;
		bullteTrav = Position.Y;
		bullife = 25;
	}	
	
	int switcher = 0;

	if (switcher == 0)//Timer Example
	{
		alphaControl += 1;
	}

	if (alphaControl == 255)
	{
		switcher = 1;
	}

	if (switcher == 1)
	{
		alphaControl -= 1;
	}

	if (alphaControl == 0)
	{
		switcher = 0;
	}
		
}

void GameLoop::LateUpdate()
{
	keypress = KMOD_NONE;
}

void GameLoop::Draw()
{
	// Objects are drawn in a painter's layer fashion meaning the first object drawn is on the bottom, and the last one drawn is on the top
	// just like a painter would paint onto a canvas
	

	Graphics::DrawCircle({100, 100}, 50, 50, { 255, 0, 255, alphaControl });
	Graphics::DrawRect(Position, { 50, 50 }, { 0, 255, 255, 255 });

	if (bullet == true)
	{
		Graphics::DrawLine({Position.X + 25, Position.Y}, { Position.X + 25, bullteTrav -= 10 }, { 255, 0, 0, 150 });
	}
	
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym , const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	case SDLK_ESCAPE: m_bRunning = false; break; // End the loop

	default:
		keypress = ac_sdlSym;
		printf("%s\n",SDL_GetKeyName(ac_sdlSym)); break;
	}
}

void GameLoop::OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	default: break;
	}
}

void GameLoop::OnExit()
{
	m_bRunning = false; // End the loop
}

GameLoop::GameLoop()
{
	m_bRunning = true;
}
GameLoop::~GameLoop()
{

}
