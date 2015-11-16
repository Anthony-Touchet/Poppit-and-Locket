#include "GameLoop.h"
#include <ctime>

Vector<float> PlayMove(400, 400);//x is player 1 y is player 2
bool move1Up = false;
bool move1Down = false;

bool move2Up = false;
bool move2Down = false;

Vector<float> Ball(790, 440);		// Ball position
bool ballMove = true;			//Which Way the ball moves
Vector<float> ballSpeed(2, 0);
Vector<int> ballSize(20, 20);
int ballMid = (ballSize.x + ballSize.y) / 2;

int PlayOneScore = 0;
int PlayTwoScore = 0;

bool p1Linestor = false;
bool p1Line = false;

System::Color<float> p1 = {0, 0, 255, 0};

bool p2Linestor = false;
bool p2Line = false;
System::Color<float> p2 = { 0, 0, 255, 0 };

int currentTime = 0;
float previousTime = 0;
float deltaTime = 0;

float timmer;
float timmer1;

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

			float div = 1000;
			float ct = clock();
			currentTime = (float)ct / div;
			deltaTime = currentTime - previousTime;

			Update();

			LateUpdate();

			Draw();

			Graphics::Flip(); // Required to update the window with all the newly drawn content
		}
	}
}

void GameLoop::Update()
{
//Moving Players
	if (move1Down == true)
	{
		PlayMove.x += 5;
	}

	if (move1Up == true)
	{
		PlayMove.x -= 5;
	}

	if (move2Down == true)
	{
		PlayMove.y += 5;
	}

	if (move2Up == true)
	{
		PlayMove.y -= 5;
	}

//Ball
	if (ballMove == true)
	{
		Ball = Ball - ballSpeed;
	}

	if (ballMove == false)
	{
		Ball = Ball + ballSpeed;
	}

	if (Ball.y == 0 || Ball.y + 20 == 900)
	{
		ballSpeed = { ballSpeed.x, -(ballSpeed.y) };
	}

	if (Ball.x + ballMid == 1600)
	{
		PlayOneScore++;
		ballMove = true;
		ballSpeed = { 4, 0 };
		Ball = {990, 440};
	}

	if (Ball.x + ballMid == 0)
	{
		PlayTwoScore++;
		ballMove = false;
		ballSpeed = { 4, 0 };
		Ball = { 340, 440 };
	}

//Player one bounce
	if(Ball.x - ballMid == 10 && Ball.y > PlayMove.x && Ball.y < PlayMove.x + 100)
	{
		ballMove = false;
		if (Ball.y + ballMid <= PlayMove.x + 25)
		{
			if (ballSpeed.x == 2 && ballSpeed.y == 2)
			{
				ballSpeed = {2, -2}; 
			}
			
			else
			{
				ballSpeed = { 2,2 };
			}
		}

		else if (Ball.y + ballMid <= PlayMove.x + 26 && Ball.y + ballMid <= PlayMove.x + 75)
		{
			ballSpeed = {5, 0};
		}

		else if (Ball.y + ballMid <= PlayMove.x + 100 )
		{
			if (ballSpeed.x == 2 && ballSpeed.y == 2)
			{
				ballSpeed = { 2, -2 };
			}

			else
			{
				ballSpeed = { 2,2 };
			}
		}
	}

	if (PlayMove.x < 0)
	{
		PlayMove.x = 0;
	}

	if (PlayMove.x + 100 > 1600)
	{
		PlayMove.x = 1600;
	}

	if (currentTime % 30 == 0 && p1Linestor == false)
	{
		p1Linestor = true;
	}

	if (p1Line == true)
	{
		p1.Alpha = 255;
		if (ballMove == true)
		{
			ballMove = false;
		}
		ballSpeed = { 10, 0 };
		timmer1 = currentTime;
		p1.Alpha = 0;
		p1Line = false;
	}

// Player2 bounce
	if (Ball.x + ballMid == 1570 && Ball.y + 20 > PlayMove.y && Ball.y < PlayMove.y + 100)
	{
		ballMove = true;
		if (Ball.y + ballMid <= PlayMove.y + 25)
		{
			if (ballSpeed.x == 2 && ballSpeed.y == 2)
			{
				ballSpeed = { 2, -2 };
			}

			else
			{
				ballSpeed = { 2,2 };
			}
		}

		else if (Ball.y + ballMid <= PlayMove.y + 26 && Ball.y + ballMid <= PlayMove.y + 75)
		{
			ballSpeed = { 5, 0 };
		}

		else if (Ball.y + ballMid <= PlayMove.y + 100)
		{
			if (ballSpeed.x == 2 && ballSpeed.y == 2)
			{
				ballSpeed = { 2, -2 };
			}

			else
			{
				ballSpeed = { 2,2 };
			}
		}
	}

	if (PlayMove.y < 0)
	{
		PlayMove.y = 0;
	}

	if (PlayMove.y + 100 > 1600)
	{
		PlayMove.y = 1600;
	}

	if (currentTime % 30 == 0 && p2Linestor == false)
	{
		p2Linestor = true;
	}

	if (p2Line == true)
	{
		p2.Alpha = 255;
		if (ballMove == false)
		{
			ballMove = true;
		}
		ballSpeed = {ballSpeed.x + 1 , ballSpeed.y};

	}

	if (currentTime == timmer + .5)
	{
		p2Line = false;
	}
}

void GameLoop::LateUpdate()
{
	
}

void GameLoop::Draw()
{
	Graphics::DrawRect({ 20, PlayMove.x }, { 10, 100 }, { 255, 255, 255, 255 });	//Player 1
	Graphics::DrawRect({ 1570, PlayMove.y }, { 10, 100 }, { 255, 255, 255, 255 });	//Player 2

	Graphics::DrawRect({ Ball.x, Ball.y }, {20, 20}, { 0, 255, 255, 255 });			//Ball

	Graphics::DrawLine({ 30, PlayMove.x + 50 }, { Ball.x + ballMid, Ball.y + 10 }, p1);	//Player One's Lazer
	Graphics::DrawLine({ 1570, PlayMove.y + 50 }, { Ball.x + ballMid, Ball.y + 10 }, p2);	//Player Two's Lazer
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym , const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	case SDLK_ESCAPE: m_bRunning = false; break; // End the loop

	default:
		switch (ac_sdlSym)	//Movement
		{
		case SDLK_s:
			move1Down = true;
			break;

		case SDLK_w:
			move1Up = true;
			break;

		case SDLK_UP:
			move2Up = true;
			break;

		case SDLK_DOWN:
			move2Down = true;
			break;

		case SDLK_d:
			if (p1Linestor == true)
			{
				p1Line = true;
			}
			break;

		case SDLK_LEFT:
			if (p1Linestor == true)
			{
				p2Line = true;
			}
			break;

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
	case SDLK_s:
		move1Down = false;
		break;

	case SDLK_w:
		move1Up = false;
		break;

	case SDLK_UP:
		move2Up = false;
		break;

	case SDLK_DOWN:
		move2Down = false;
		break;

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

