//Make a two player tic tac toe game.
//? Modify the program so that it will announce when a player has won the game(and which player won, x or o)
//?? Modify the program so that it is a one player game against the computer(with the computer making its moves randomly)
//???? Modify the program so that anytime the player is about to win(aka, they have 2 of 3 x's in a row, the computer will block w/ an o)

#include "TicTacToe.h"

int main()
{
	TTS space1(1);
	TTS space2(2);
	TTS space3(3);
	TTS space4(4);
	TTS space5(5);
	TTS space6(6);
	TTS space7(7);
	TTS space8(8);
	TTS space9(9);

	TTS spacearry[9] = {space1, space2, space3, space4, space5, space6, space7, space8, space9 };

	bool *playerTurn = new bool(true); //Player 1 is true. Player 2 is false

	bool *running = new bool (true);

	while (*running == true)
	{
//Player's Turn
		if (*playerTurn == true)
		{
			cout << "Player x's turn.\n";
		}

		else
		{
			cout << "Player o's turn.\n";
		}

//Print Board		
		for (int num = 1; num < 10; num++)
		{
			if (num % 3 == 0)
			{
				if (spacearry[num - 1].owner == NULL)
				{
					cout << spacearry[num - 1].num << endl;
				}

				else
				{
					cout << spacearry[num - 1].owner << "  ";
				}
			}

			else
			{
				if (spacearry[num - 1].owner == NULL)
				{
					cout << spacearry[num - 1].num << "  ";
				}

				else
				{
					cout << spacearry[num - 1].owner << "  ";
				}
			}
		}

//Player's choice
		int choice;
		cout << "If ";
		
//Is the game still going
		for (int id = 1; id < 11; id++)//Game resetter
		{
			TTS current = spacearry[id];
			
			if (current.owner == NULL)//if there is still a space.
			{
				break;
			}

			if (id == 10)//No Space with NUll
			{
				*running = false;
				break;
			}
		}



	}


}