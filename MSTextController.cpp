
#include <iostream>
#include <string>
#include "MSTextController.h"

using namespace std;


MSTextController::MSTextController(MinesweeperBoard& board2, MSBoardTextView& view2) :board(board2), view(view2)
{
}

int MSTextController::getX()
{
	int col = 0;
	cout << "Podaj pozycje na osi X od 1 do " << board.getBoardWidth() << " : ";
	cin >> col;
	while (col >= 1 && col <= board.getBoardWidth())
	{
		if (col < 1 || col > board.getBoardWidth())
		{
			cout << "Podaj pozycjê która znajduje siê na planszy!" << endl;
			cin >> col;
		}
		else
		{
			return col;
		}
	}
}

int MSTextController::getY()
{
	int row = 0;
	cout << "Podaj pozycje na osi Y od 1 do " << board.getBoardHeight() << " : ";
	cin >> row;
	while (row >= 1 && row <= board.getBoardHeight())
	{
		if (row < 1 || row > board.getBoardHeight())
		{
			cout << "Podaj pozycjê która znajduje siê na planszy!" <<endl;
			cin >> row;
		}
		else
		{
			return row;
		}
	}
}

int MSTextController::Win()
{

	return 0;
}

void MSTextController::play()
{
	while (board.getGameState() == RUNNING)
	{
		int x, y, menu;
		view.display();
		cout << "Podaj co chcesz zrobic:" << endl;
		cout << "1. Odkryc pole." << endl;
		cout << "2. Postawic flage." << endl;
		cout << "3. Usunac flage." << endl;
		cin >> menu;
		switch (menu)
		{
		case 1:
			cout << "Ktore pole chcesz odkryc?" << endl;
			y = getY();
			x = getX();
			if (x != -1 && y != -1)
			{
				board.revealField(y - 1, x - 1);
			}
			break;
		case 2:
			cout << "Ktore pole chcesz oznaczyc falga?" <<endl;
			y = getY();
			x = getX();
			if (x != -1 && y != -1)
			{
				board.toggleFlag(y - 1, x - 1);
			}
			board.debug_display();
			break;
		case 3:
			cout << "Z ktorego pola chcesz pozbyc sie flagi?" << endl;
			y = getY();
			x = getX();
			if (x != -1 && y != -1)
			{
				board.toggleFlag(y - 1, x - 1);
			}
		default: cout << "ERROR" << endl;
			break;
		}
	}
	if (board.getGameState() == FINISHED_LOSS)
	{
		cout << "KONIEC";
	}
	if (board.getGameState() == FINISHED_WIN)
	{
		cout << "KONIEC";
	}

}