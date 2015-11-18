#include "GameLoop.h"
#include <ctime>

float Mod(float, float);

Vector<float> PlayMove(400, 400);//x is player 1 y is player 2
bool move1Up = false;
bool move1Down = false;

bool move2Up = false;
bool move2Down = false;

Vector<int> Ball(800, 450);		// Ball position
bool ballMove = true;			//Which Way the ball moves
Vector<int> ballSpeed(4, 0);
Vector<int> ballSize(20, 20);
int ballMid = ballSize.x / 2;

int PlayOneScore = 0;
bool pu1 = true;

int PlayTwoScore = 0;
bool pu2 = true;

int currentTime = 0;
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

			LateUpdate();

			Draw();

			Graphics::Flip(); // Required to update the window with all the newly drawn content
		}
	}
}


void GameLoop::LateUpdate()
{
	if (PlayOneScore < 10 && PlayTwoScore < 10)
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
		if (ballSpeed.y >= 11)//Speed controlers
		{
			ballSpeed.y = 2;
		}
	
		if (ballSpeed.x >= 11)
		{
			ballSpeed.x = 10;
		}

		if (ballMove == true)// Left to right
		{
			Ball = Ball - ballSpeed;
		}

		if (ballMove == false)
		{
			Ball = Ball + ballSpeed;
		}

		if (Ball.y - ballMid <= 0 || Ball.y + ballMid >= 900) //Ball side Barrier
		{
			ballSpeed = { ballSpeed.x, -(ballSpeed.y) };
		}

		if (Ball.x - ballMid >= 1600) //Player one scores
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
		if (Ball.x - ballMid <= 30 && Ball.x - ballMid >= 20 && Ball.y >= PlayMove.x && Ball.y <= PlayMove.x + 100 || Ball.y - ballMid <= PlayMove.x + 100 && Ball.y + ballMid >= PlayMove.x && Ball.x - ballMid <= 30 && Ball.x - ballMid >= 20)
		{
			ballMove = false;
			if (ballSpeed.y == 0)
			{
				ballSpeed = { ballSpeed.x + 1, ballSpeed.y - 1 };
			}

			else if (ballSpeed.y > 0)
			{
				ballSpeed = { ballSpeed.x + 1, -(ballSpeed.y) - 1 };
			}

			else if (ballSpeed.y < 0)
			{
				ballSpeed = { ballSpeed.x + 1, -(ballSpeed.y) + 1 };
			}
		}

		if (PlayMove.x < 0)
		{
			PlayMove.x = 0;
		}

		if(currentTime % 15 == 0)
		{ 
			pu1 = true;
			pu2 = true;
		}

		if (PlayMove.x + 100 >= 900)
		{
			PlayMove.x = 800;
		}

		// Player2 bounce
		if (Ball.x + ballMid >= 1570 && Ball.x + ballMid <= 1580 && Ball.y >= PlayMove.y && Ball.y <= PlayMove.y + 100 || Ball.y - ballMid <= PlayMove.y + 100 && Ball.y + ballMid >= PlayMove.y && Ball.x + ballMid <= 1580 && Ball.x + ballMid >= 1570)
		{
			ballMove = true;
			if (ballSpeed.y == 0)
			{
				ballSpeed = { ballSpeed.x + 1, ballSpeed.y + 1 };
			}
	
			else if (ballSpeed.y > 0)
			{
				ballSpeed = { ballSpeed.x + 1, -(ballSpeed.y) - 1 };
			}

			else if (ballSpeed.y < 0)
			{
				ballSpeed = { ballSpeed.x + 1, -(ballSpeed.y) + 1 };
			}
		}

		if (PlayMove.y <=  0)
		{
			PlayMove.y = 0;
		}

		if (PlayMove.y + 100 >= 900)
		{
			PlayMove.y = 800;
		}
	}

}

void GameLoop::Draw()
{
	if (PlayOneScore < 10 && PlayTwoScore < 10)
	{
		Graphics::DrawLine({ 800, 0 }, { 800, 900 }, { 255, 0, 0, 255 });	//Boundry
		

		Graphics::DrawRect({ 20, PlayMove.x }, { 10, 100 }, { 255, 255, 255, 255 });	//Player 1


		Graphics::DrawRect({ 1570, PlayMove.y }, { 10, 100 }, { 255, 255, 255, 255 });	//Player 2
	
		if (pu1 == true)
		{
			Graphics::DrawCircle({ 300, 10 }, 5, 20, { 0, 255, 255, 25 });
		}

		if (pu2 == true)
		{
			Graphics::DrawCircle({ 1300, 10 }, 5, 20, { 0, 255, 255, 25 });
		}

	//Points 
	//Player 1
	if (PlayOneScore < 10 && PlayTwoScore < 10)
	{
		switch (PlayOneScore)
		{
		case 0:
			Graphics::DrawRect({ 395, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//0
			Graphics::DrawRect({ 445, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 10 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

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
			Graphics::DrawRect({ 395, 55 }, { 50, 10 }, { 255, 255, 255, 255 });	//4
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
			Graphics::DrawRect({ 395, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//7
			Graphics::DrawRect({ 445, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			break;

		case 8:
			Graphics::DrawRect({ 395, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//8
			Graphics::DrawRect({ 445, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 50 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 10 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		case 9:
			Graphics::DrawRect({ 395, 10 }, { 10, 50 }, { 255, 255, 255, 255 });	//9
			Graphics::DrawRect({ 445, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 50 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 10 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 395, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		default:
			break;
		}
		
		
	}
		//Player 2
	if (PlayOneScore < 10 && PlayTwoScore < 10)
	{
		switch (PlayTwoScore)
		{
		case 0:
			Graphics::DrawRect({ 1205, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//0
			Graphics::DrawRect({ 1255, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 10 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		case 1:
			Graphics::DrawRect({ 1205, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//1
			break;

		case 2:
			Graphics::DrawRect({ 1205, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//2
			Graphics::DrawRect({ 1255, 10 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 50 }, { 60, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 50 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 90 }, { 60, 10 }, { 255, 255, 255, 255 });
			break;

		case 3:
			Graphics::DrawRect({ 1205, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//3
			Graphics::DrawRect({ 1255, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 55 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		case 4:
			Graphics::DrawRect({ 1205, 55 }, { 50, 10 }, { 255, 255, 255, 255 });	//4
			Graphics::DrawRect({ 1255, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 10 }, { 10, 50 }, { 255, 255, 255, 255 });
			break;

		case 5:
			Graphics::DrawRect({ 1215, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//5
			Graphics::DrawRect({ 1205, 10 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 50 }, { 60, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1255, 50 }, { 10, 40 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 90 }, { 60, 10 }, { 255, 255, 255, 255 });
			break;

		case 6:
			Graphics::DrawRect({ 1105, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//6
			Graphics::DrawRect({ 1160, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1160, 55 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1215, 55 }, { 10, 55 }, { 255, 255, 255, 255 });
			break;

		case 7:
			Graphics::DrawRect({ 1205, 10 }, { 50, 10 }, { 255, 255, 255, 255 });	//7
			Graphics::DrawRect({ 1255, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			break;

		case 8:
			Graphics::DrawRect({ 1205, 10 }, { 10, 100 }, { 255, 255, 255, 255 });	//8
			Graphics::DrawRect({ 1255, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 50 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 10 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		case 9:
			Graphics::DrawRect({ 1205, 10 }, { 10, 50 }, { 255, 255, 255, 255 });	//9
			Graphics::DrawRect({ 1255, 10 }, { 10, 100 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 50 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 10 }, { 50, 10 }, { 255, 255, 255, 255 });
			Graphics::DrawRect({ 1205, 100 }, { 50, 10 }, { 255, 255, 255, 255 });
			break;

		default:
			break;
		}
		
		
		}
	Graphics::DrawCircle({ Ball.x, Ball.y }, ballSize.x, 20, { 0, 255, 255, 255 });
	}

	else
	{
		if (PlayOneScore >= 10)
		{
			cout << "Player 1 Wins!!\n";
			system("pause");
			m_bRunning = false;
		}

		if (PlayTwoScore >= 10)
		{
			cout << "Player 2 Wins!!\n";
			system("pause");
			m_bRunning = false;
		}
	}
}			//Ball

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

		case SDLK_d:
			if (pu1 == true)
			{
				ballSpeed = { ballSpeed.x, -(ballSpeed.y) };
				pu1 = false;
			}
			break;

		case SDLK_UP:
			move2Up = true;
			break;

		case SDLK_DOWN:
			move2Down = true;
			break;

		case SDLK_LEFT:
			if (pu2 == true)
			{
				ballSpeed = { ballSpeed.x, -(ballSpeed.y) };
				pu2 = false;
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