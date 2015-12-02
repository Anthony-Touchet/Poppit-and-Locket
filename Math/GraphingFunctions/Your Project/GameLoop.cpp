#include "GameLoop.h"
#include <ctime>

Vector<float> GetNumber();
Vector<float> AddTwo();
float DegreestoRads();
Vector<float> LinTin();
Vector<float>(*Graph)() = &GetNumber;
float(*Number)() = &DegreestoRads;
bool graph = false;
float incx;
float incy;

bool num = false;

float currentTime = 0;
float previousTime = 0;
float deltaTime = 0;

Vector<int> Position = { 50, 450 };
Vector<int> Color(255, 0, 0, 255);

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

			Update();//Will mostly control moving objects

			Draw();

			Graphics::Flip(); // Required to update the window with all the newly drawn content
		}
	}
}

void GameLoop::Update()
{
	float control = 2.5;
	if (previousTime <= currentTime)
	{
		Position.x += 3;
	}

	if (Position.x - 50 >= 1600)
	{
		Position.x = 50;
	}
}

void GameLoop::Draw()
{
	Graphics::DrawCircle({ Position.x, Position.y }, 50, 50, { Color.x, Color.y, Color.z, Color.alpha });

	Graphics::DrawLine({ 25, 875 }, {1600, 875}, {255, 0, 0, 255});// X Axis
	Graphics::DrawLine({ 25, 875 }, { 25, 0 }, { 255, 0, 0, 255 });//Y Axis
	
	//X Increments
	float x = 25;
	for (int i = 0; i < 32; i++)
	{
		x += 50;
		Graphics::DrawLine({x , 875 }, { x, 0 }, { 0, 0, 255, 255 });
	}

	//Y increments
	float y = 875;
	for (int i = 0; i < 32; i++)
	{
		y -= 50;
		Graphics::DrawLine({ 25, y }, { 1600, y }, { 0, 0, 255, 255 });
	}

	//Test Function
	if (graph == true)
	{
//Function manipulation
		Vector<float> inc(Graph());
		inc.y *= -1;		//To go up in this program you need to decrement y. in actual graphing you increase y. This is here to convert from engine to actual graphing.

		Graphics::DrawLine({ 25, 875 }, { 25 + (inc.x * 50), 875 + (inc.y * 50) }, { 0, 255, 0, 255 });
		incx = inc.x * 50;
		incy = inc.y * 50;
		cout << inc.x << ", "<< inc.y << endl;
		graph = false;
	}

	Graphics::DrawLine({ 25, 875 }, { 25 + incx, 875 + incy }, { 0, 255, 0, 255 });
	
	if (num == true)
	{
		float inc(Number());
		cout << inc << endl;
		num = false;
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
		case SDLK_g:
			int controler;
			cout << "Press 1 to graph one function.\nPress 2 to add two together.\nPress 3 to turn Degrees to Radians.\nPress 4 to find a ceratin point between two numbers.\nAny Error will result in one being default.\n";
			cin >> controler;

			if (controler == 2)
			{
				graph = true;
				Graph = &AddTwo;
			}

			else if (controler == 3)
			{
				num = true;
				Number = &DegreestoRads;
			}

			else if (controler == 4)
			{
				num = true;
				Graph = &LinTin;
			}

			else
			{
				graph = true;
				Graph = &GetNumber;
			}
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

Vector<float> GetNumber()//Basic graphing Vectors
{
	Vector<float> N(0, 0);
	cout << "Please Enter a X increment for the function.\n";
	cin >> N.x;
	cout << "Please Enter a Y increment for the function.\n";
	cin >> N.y;
	return N;
}

Vector<float> AddTwo()//Adding two vectors
{
	Vector<float> N(0, 0);
	cout << "Please Enter a X increment for Vector 1.\n";
	cin >> N.x;
	cout << "Please Enter a Y increment for Vector 1.\n";
	cin >> N.y;

	Vector<float> Z(0, 0);
	cout << "Please Enter a X increment for Vector 2.\n";
	cin >> Z.x;
	cout << "Please Enter a Y increment for Vector 2.\n";
	cin >> Z.y;

	return N + Z;
}

float DegreestoRads()//Converts Degrees to radians
{
	Vector<int> x(0,0,0);
	cout << "Please Enter an integer for Degrees.\n";
	cin >> x.x;

	return x.DtoR(x.x);
}

Vector<float> LinTin()//Linniar Interpolation
{
	Vector<float> a(0,0);
	Vector<float> b(0, 0);
	Vector<float> c(0, 0);
	float per;
	cout << "Enter an X value starting vector.\n";
	cin >> a.x;

	cout << "Enter an Y value starting vector.\n";
	cin >> a.y;

	cout << "Enter an X value ending vector.\n";
	cin >> b.x;

	cout << "Enter an Y value ending vector.\n";
	cin >> b.y;

	cout << "Enter a percentage in the form of a decimal to find the middle of these two Vectors.\nExample: 25% is .25.\n";
	cin >> per;

	c.x = c.LinearInterpolation(a.x, b.x, per);
	c.y = c.LinearInterpolation(a.y, b.y, per);
	return c;
}