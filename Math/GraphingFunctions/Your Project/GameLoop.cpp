#include "GameLoop.h"
#include <ctime>

Vector<float> GetNumber();
Vector<float>(*Graph)() = &GetNumber;

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

			Draw();

			Graphics::Flip(); // Required to update the window with all the newly drawn content
		}
	}
}

void GameLoop::Draw()
{
	Graphics::DrawLine({ 25, 875 }, {1600, 875}, {255, 0, 0, 255});// X Axis
	Graphics::DrawLine({ 25, 875 }, { 25, 0 }, { 255, 0, 0, 255 });//Y Axis
	
	//X Increments
	float x = 25;
	for (int i = 0; i < 32; i++)
	{
		x += 50;
		Graphics::DrawLine({x , 865 }, { x, 885 }, { 0, 0, 255, 255 });
	}

	//Y increments
	float y = 875;
	for (int i = 0; i < 32; i++)
	{
		y -= 50;
		Graphics::DrawLine({ 15, y }, { 35, y }, { 0, 0, 255, 255 });
	}

	//Test Function
	float incx, incy;
	Vector<float> inc(Graph());		//Incrementing Variables
	float f1x, f1y;					//Function's start point

	//Function manipulation

	f1x = 25;			//Start Position X
	f1y = 875;			//Start Position Y
	inc.y *= -1;		//To go up in this program you need to decrement y. in actual graphing you increase y. This is here to convert from engine to actual graphing.

	for (int w = 0; w < 5; w++)
	{
		Graphics::DrawLine({ f1x, f1y }, { f1x + (inc.x * 5), f1y + (inc.y * 5) }, { 0, 0, 255, 255 });
		f1x = f1x + (inc.x * 5);
		f1y = f1y + (inc.y * 5);
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

Vector<float> GetNumber()
{
	Vector<float> N(0, 0);
	cout << "Please Enter a X increment.\n";
	cin >> N.x;
	cout << "Please Enter a Y increment.\n";
	cin >> N.y;
	return N;
}