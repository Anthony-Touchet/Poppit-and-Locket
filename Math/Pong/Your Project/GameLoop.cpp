#include "GameLoop.h"
#include <ctime>

Vector<float> PlayMove(400, 400);//x is player 1 y is player 2
bool move1Up = false;
bool move1Down = false;

bool move2Up = false;
bool move2Down = false;

Vector<int> Ball(800, 440);		// Ball position
bool ballMove = true;			//Which Way the ball moves
Vector<int> ballSpeed(4, 0);
Vector<float> ballSize(20, 20);
int ballMid = ballSize.x / 2;

int PlayOneScore = 0;
int powerUp1 = 0;
bool drop1 = true;

int PlayTwoScore = 0;
int powerUp2 = 0;

float currentTime = 0;
float previousTime = 0;
float deltaTime = 0;

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

	if (Ball.x + ballMid >= 1600) //Player one scores
	{
		PlayOneScore++;
		ballMove = true;
		ballSpeed = { 4, 0 };
		Ball = { 1000, 440 };
	}

	if (Ball.x + ballMid <= 0) //Player two scores
	{
		PlayTwoScore++;
		ballMove = false;
		ballSpeed = { 4, 0 };
		Ball = { 340, 440 };
	}

	//Player one bounce
	if (Ball.x - ballMid <= 30 && Ball.x - ballMid >= 20 && Ball.y > PlayMove.x && Ball.y < PlayMove.x + 100)
	{
		ballMove = false;

		if (Ball.y + ballMid <= PlayMove.x + 25)
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

		else if (Ball.y + ballMid <= PlayMove.x + 26 && Ball.y + ballMid <= PlayMove.x + 75)
		{
			ballSpeed = { 5, 0 };
		}

		else if (Ball.y + ballMid <= PlayMove.x + 100)
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

	if (PlayMove.x + 100 >= 900)
	{
		PlayMove.x = 800;
	}

	if (powerUp1 != 0)
	{
		/*if (currentTime % 7 == 0)
		{
			drop1 = true;
		}*/
	}

	// Player2 bounce
	if (Ball.x + ballMid >= 1570 && Ball.x + ballMid <= 1580 && Ball.y + 20 > PlayMove.y && Ball.y < PlayMove.y + 100)
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

	if (PlayMove.y + 100 >= 900)
	{
		PlayMove.y = 800;
	}
}

void GameLoop::LateUpdate()
{

}

void GameLoop::Draw()
{
	Graphics::DrawLine({ 800, 0 }, { 800, 900 }, {255, 0, 0, 255});	//Boundry
	Graphics::DrawCircle({ Ball.x, Ball.y },  20, 20 , { 0, 255, 255, 255 });			//Ball

	Graphics::DrawRect({ 20, PlayMove.x }, { 10, 100 }, { 255, 255, 255, 255 });	//Player 1
	if (drop1 == true)
	{
		Graphics::DrawCircle({ 200, 50 }, 20, 20, { 0, 255, 255, 255 });
	}

	Graphics::DrawRect({ 1570, PlayMove.y }, { 10, 100 }, { 255, 255, 255, 255 });	//Player 2

	//Points
	if (PlayOneScore < 10)
	{
		switch (PlayOneScore)
		{
		case 1:
			Graphics::DrawRect({ 395, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//1
			break;

		case 2:
			Graphics::DrawRect({ 395, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//2
			Graphics::DrawRect({ 445, 10 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 50 }, { 60, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 50 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 90 }, { 60, 10 }, { 255, 255, 255, 255 });
			break;

		case 3:
			Graphics::DrawRect({ 395, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//3
			Graphics::DrawRect({ 445, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 55 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		case 4:
			Graphics::DrawRect({ 395, 55 }, { 50, 10 }, { 255, 255, 255, 255 });			//4
			Graphics::DrawRect({ 445, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 10 }, { 10, 50 }, { 255, 255, 255, 255 });
			break;

		case 5:
			Graphics::DrawRect({ 405, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//5
			Graphics::DrawRect({ 395, 10 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 50 }, { 60, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 445, 50 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 90 }, { 60, 10 }, { 255, 255, 255, 255 });
			break;

		case 6:
			Graphics::DrawRect({ 345, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//6
			Graphics::DrawRect({ 355, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 355, 55 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 405, 55 }, { 10, 55 }, { 255, 255, 255, 255 });
			break;

		case 7:
			break;
		}
	}
}

void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
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
			if (drop1 == true)
			{
				Vector<int> old = ballSpeed;
				ballSpeed = { 0, -10 };
				if (currentTime - .1 <= previousTime)
				{
					drop1 = false;
					ballSpeed = old;
				}
			}
			break;

		case SDLK_LEFT:
			if (drop1 == true)
			{
				Vector<int> old = ballSpeed;
				ballSpeed = { 0, 10 };
				if (currentTime % 5 += previousTime )
				{
					drop1 = false;
					ballSpeed = old;
				}
			}
			break;

		default:
			break;
		}
		printf("%s\n", SDL_GetKeyName(ac_sdlSym)); break;//Prints Keystroke to other console window.
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

