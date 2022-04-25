#include <iostream>
#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"

using namespace std;

MSBoardTextView::MSBoardTextView(MinesweeperBoard& board) :board(board)
{
}

MSBoardTextView::MSBoardTextView(const MSBoardTextView& view2) : board(view2.board)
{
}

void MSBoardTextView::display() const
{
    cout << "   ";
    for (int num = 0; num < board.getBoardWidth(); num++)
    {
        if (num < 9)
            cout << " " << num + 1 << " ";
        if (num >= 9 && num < 99)
            cout << num + 1 << " ";
        if (num >= 99)
            cout << num + 1;
    }
    cout << endl;
    for (int row = 0; row < board.getBoardHeight(); row++)
    {
        if (row < 9)
        {
            cout << " " << row + 1 << " ";
        }
        if (row >= 9 && row < 99)
        {
            cout << row + 1 << " ";
        }
        if (row >= 99)
        {
            cout << row + 1;
        }
        for (int col = 0; col < board.getBoardWidth(); col++)
        {
            cout << "[";
            if (board.isRevealed(row, col) == 0 && board.hasFlag(row, col) == 0)
            {
                cout << " ";
            }
            if (board.hasFlag(row, col) == 1)
            {
                cout << "F";
            }
            if (board.isRevealed(row, col) == 1 && board.hasFlag(row, col) == 0)
            {
                cout << board.countMines(row, col);
            }
            cout << "]";
        }
        cout << "\n";

    }
    cout << endl;
}