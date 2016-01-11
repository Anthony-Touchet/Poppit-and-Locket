//Write a program which will find all such numbers which are divisible by 7 but are not a multiple of 5,
//between 2000 and 3200 (both included).
//The numbers obtained should be printed in a comma - separated sequence on a single line.

using namespace std;
#include <iostream>
#include <string>

int main()
{
	for(int in = 2000; in <= 3200; in++)
		{
			if (in % 7 == 0 && in % 5 != 0)
			{
				cout << in << ", ";
			}
		}

	cout << "\n";

	system("pause");

	range(2000, 3200);
}
