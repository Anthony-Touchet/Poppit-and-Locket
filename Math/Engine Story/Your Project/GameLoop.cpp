#include "GameLoop.h"
#include <ctime>

Vector<int> Position = { 50, 400 };
System::Color<int> OutterMan = { 0.0, 0.0, 255.0, 255.0 };
System::Color<int> Hearts = { 0, 0, 255, 255 };
bool inner = true;
bool together = false;
bool ties1 = true;
bool ties2 = false;
bool ties3 = false;
bool fireworks = false;

int currentTime = 0;
float previousTime = 0;
float deltaTime = 0;

int alphaControl = 255;

bool heartr = false;
bool heartb = true;
bool heartg = false;

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

			float div = 1000;
			float ct = clock();
			currentTime = (float) ct / div;
			deltaTime = currentTime - previousTime;

			//Blue heart controller
			if (heartb == true)
			{
				Hearts.Blue -= 5;
			}

			if (Hearts.Blue == 0)
			{
				heartb == false;
			}

			if (heartb == false)
			{
				Hearts.Blue += 5;
			}

			if (Hearts.Blue == 250)
			{
				heartb == true;
			}

			//Red heart controller
			if (heartr == true)
			{
				Hearts.Red -= 50;
			}

			if (Hearts.Red == 0)
			{
				heartr == false;
			}

			if (heartr == false)
			{
				Hearts.Red += 50;
			}

			if (Hearts.Red == 250)
			{
				heartr == true;
			}

			//Green heart controller
			if (heartg == true)
			{
				Hearts.Green -= 25;
			}

			if (Hearts.Green == 0)
			{
				heartg == false;
			}

			if (heartg == false)
			{
				Hearts.Green += 25;
			}

			if (Hearts.Green == 250)
			{
				heartg == true;
			}

			if (Position.x != 1100)//Not at Girl yet
			{
				if (ties2 == false && ties3 == false)//tie 1
				{
					(Position.x += 5) * deltaTime;
				}

				if (ties2 == true && ties3 == false)// tie 2
				{
					(Position.x += 2) * deltaTime;
				}

				if (ties2 == true && ties3 == true)//tie 3
				{
					(Position.x += 1) * deltaTime;
				}

				if (OutterMan.Blue != 0)//Outter layer fade 
				{
					(OutterMan.Blue -= 0.5) * deltaTime;
				}

				else if (OutterMan.Red != 255 && currentTime % 2 == 0)//Ounce outer layyer out new outer layer
				{
					(OutterMan.Red += 1) * deltaTime;
					if (OutterMan.Green != 100)
					{
						(OutterMan.Green += 1) * deltaTime;
					}
				}

				if (Position.x == 300)//tie 2 trigger
				{
					ties2 = true;
				}

				if (Position.x == 600)//tie 3 trigger
				{
					ties3 = true;
				}
			}

			if (Position.x == 1100)//At woman
			{
				alphaControl = 0;
				ties1 = false;
				ties2 = false;
				ties3 = false;
			}

			if (Position.x == 1100 && currentTime % 5 == 0)//Becomes full man
			{
				OutterMan = { 0, 0, 255, 255 };
				inner = false;
			}

			if (Position.x == 1100 && inner == false)//fireworks
			{
				if (fireworks == false)
				{
					fireworks = true;
				}

				else
				{
					fireworks = false;
				}
			}

			if (Position.x == 1100 && currentTime % 9 == 0)//two become one
			{
				together = true;
			}

			if (currentTime == 20)// end
			{
				m_bRunning = false;
			}

			Draw();

			previousTime = currentTime;

			Graphics::Flip(); // Required to update the window with all the newly drawn content
		}
	}
}

void GameLoop::Draw()
{
	if (together == false)
	{
		Graphics::DrawCircle({ Position.x, Position.y }, 50, 50, OutterMan);	//Outer Man
		if (inner == true)
		{
			Graphics::DrawCircle({ Position.x, Position.y }, 25, 25, { 0, 0, 255, 255 });//Inner Man
		}
		Graphics::DrawCircle({ 1200, 400 }, 50, 50, { 255, 0, 255, 200 });//Woman
		
		//Enemies
		Graphics::DrawCircle({ 150, 250 }, 15, 30, { 0, 255, 0, alphaControl });
		Graphics::DrawCircle({ 150, 550 }, 15, 30, { 0, 255, 0, alphaControl });

		Graphics::DrawCircle({ 450, 250 }, 15, 30, { 0, 255, 0, alphaControl });
		Graphics::DrawCircle({ 450, 550 }, 15, 30, { 0, 255, 0, alphaControl });

		Graphics::DrawCircle({ 750, 250 }, 15, 30, { 0, 255, 0, alphaControl });
		Graphics::DrawCircle({ 750, 550 }, 15, 30, { 0, 255, 0, alphaControl });

		if (ties1 == true)//Shots
		{
			Graphics::DrawLine({ 150, 250 }, { Position.x, Position.y }, Hearts);
			Graphics::DrawLine({ 150, 550 }, { Position.x, Position.y }, Hearts);
		}

		if (ties2 == true)
		{
			Graphics::DrawLine({ 450, 250 }, { Position.x, Position.y }, Hearts);
			Graphics::DrawLine({ 450, 550 }, { Position.x, Position.y }, Hearts);
		}

		if (ties3 == true)
		{
			Graphics::DrawLine({ 750, 250 }, { Position.x, Position.y }, Hearts);
			Graphics::DrawLine({ 750, 550 }, { Position.x, Position.y }, Hearts);
		}
	}

	//Fireworks
	if (fireworks == true)
	{
		Graphics::DrawCircle({ 1150, 300 }, 30, 3, Hearts);//Heart1
		Graphics::DrawCircle({ 1135, 300 }, 15, 3, Hearts);
		Graphics::DrawCircle({ 1125, 315 }, 15, 30, Hearts);
		Graphics::DrawCircle({ 1125, 285 }, 15, 30, Hearts);

		Graphics::DrawCircle({ 1150, 500 }, 30, 3, Hearts);//Heart2
		Graphics::DrawCircle({ 1135, 500 }, 15, 3, Hearts);
		Graphics::DrawCircle({ 1125, 515 }, 15, 30, Hearts);
		Graphics::DrawCircle({ 1125, 485 }, 15, 30, Hearts);

		if (together == true)
		{
			Graphics::DrawCircle({ 1050, 400 }, 30, 3, Hearts);//Heart3
			Graphics::DrawCircle({ 1035, 400 }, 15, 3, Hearts);
			Graphics::DrawCircle({ 1025, 415 }, 15, 30, Hearts);
			Graphics::DrawCircle({ 1025, 385 }, 15, 30, Hearts);

			Graphics::DrawCircle({ 1250, 400 }, 30, 3, Hearts);//Heart4
			Graphics::DrawCircle({ 1235, 400 }, 15, 3, Hearts);
			Graphics::DrawCircle({ 1225, 415 }, 15, 30, Hearts);
			Graphics::DrawCircle({ 1225, 385 }, 15, 30, Hearts);
		}

		else
		{
			Graphics::DrawCircle({ 1000, 400 }, 30, 3, Hearts);//Heart3
			Graphics::DrawCircle({ 985, 400 }, 15, 3, Hearts);
			Graphics::DrawCircle({ 975, 415 }, 15, 30, Hearts);
			Graphics::DrawCircle({ 975, 385 }, 15, 30, Hearts);

			Graphics::DrawCircle({ 1300, 400 }, 30, 3, Hearts);//Heart4
			Graphics::DrawCircle({ 1285, 400 }, 15, 3, Hearts);
			Graphics::DrawCircle({ 1275, 415 }, 15, 30, Hearts);
			Graphics::DrawCircle({ 1275, 385 }, 15, 30, Hearts);
		}
	}

	if (together == true)
	{
		Graphics::DrawCircle({ 1150 , 400 }, 50, 50, { 150, 0, 255, 255 });//Together Forever
	}

	
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym , const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	case SDLK_ESCAPE: m_bRunning = false; break; // End the loop

	default:
		switch (ac_sdlSym)	//Movement
		{
		case SDLK_t:
			cout << currentTime << "\n" << previousTime << "\n" << deltaTime << endl;

		default:
			break;
		}
		printf("%s\n",SDL_GetKeyName(ac_sdlSym)); break;//Prints Keystroke to other console window.
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