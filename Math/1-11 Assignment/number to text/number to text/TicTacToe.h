using namespace std;
#include <iostream>
#include <string>

class TTS
{
public:
	char owner;	//who controls this space
	int num;	//space identity
	TTS();
	TTS(int);
};

TTS::TTS(int nu)//Constructor
{
	num = nu;
	owner = NULL;
}

TTS::TTS()//Constructor
{
	num = 0;
	owner = NULL;
}