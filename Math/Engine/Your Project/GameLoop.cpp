#include "GameLoop.h"

System::Point2D<float> Position = { 800, 450 };
int timer = 0;
int alphaControl = 1;

int speed = 25;// Box speed

bool bullet = false;//is there a bullet on the screen
float bulletTrav = Position.Y;
int bullife = 80;

bool hit = false;

bool swittcher = false;

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

//Bullet
	if (bullet == true && bullife > 0)//Bullet keeps going
	{
		bullife -= 1;
	}

	else//Bullet stops
	{
		bullet = false;
		bulletTrav = Position.Y;
		bullife = 80;
	}

//Timer Example
	if (swittcher == false)//fade in
	{
		alphaControl += 1;
	}
	
	else if (swittcher == true)//fade out
	{
		alphaControl -= 1;
	}

	if (alphaControl == 255)//trigger to fade out
	{
		swittcher = true;
	}
	
	if (alphaControl == 0)//trigger to fade in
	{
		swittcher = false;
	}
}

void GameLoop::LateUpdate()
{
//Bullet
	if (Position.X + 25 == 800 && bulletTrav - 5 == 150 && bullet == true)//Bullet hits preset point
	{
		hit = true;
		bullet = false;
		printf("hit");
	}
}

void GameLoop::Draw()
{
	// Objects are drawn in a painter's layer fashion meaning the first object drawn is on the bottom, and the last one drawn is on the top
	// just like a painter would paint onto a canvas
	

	Graphics::DrawCircle({ 800, 100 }, 50, 50, {255, 0, 255, alphaControl});	//Timer Example
	Graphics::DrawRect(Position, { 50, 50 }, { 0, 255, 255, 255 });				//Player

	if (bullet == true)//If the bullet has been shot
	{
		Graphics::DrawRect({ Position.X + 25, bulletTrav -= 5 }, {3, 3}, { 255, 0, 0, 150 });	//Bullet
	}
	
	if (hit == true)	//If bullet hits the point
	{
		Graphics::DrawCircle({ 100, 100 }, 50, 50, { 255, 0, 255, 255 });	//Confirmation Circle
	}

	hit = false;	//Reset hit to false
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym , const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	case SDLK_ESCAPE: m_bRunning = false; break; // End the loop

	default:
		switch (ac_sdlSym)	//Movement
		{
		case SDLK_KP_5:	//Down
			Position.Y += speed;
			break;

		case SDLK_KP_8:	//Up
			Position.Y -= speed;
			break;

		case SDLK_KP_4:	//Left
			Position.X -= speed;
			break;

		case SDLK_KP_6:	//Right
			Position.X += speed;
			break;

		case SDLK_w:	//Shoot up
			bullet = true;
			break;

		default:
			break;
		}
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
