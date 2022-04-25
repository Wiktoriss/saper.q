#include <iostream>
#include <string> 
#include <vector>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"


using namespace std;
MinesweeperBoard::MinesweeperBoard()
{

}


MinesweeperBoard::MinesweeperBoard(int szer, int wys, GameMode mode)
{
    height = wys;
    width = szer;
    state = RUNNING;
    minecount = 0;
    srand(time(NULL));
    FirstMove = true;


    switch (mode)
    {
    case DEBUG:
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                if (row == col)
                {
                    board[row][col].hasMine = 1;
                }
                if (row == 0)
                {
                    board[row][col].hasMine = 1;
                }
                if (col == 0 && row % 2 == 0)
                {
                    board[row][col].hasMine = 1;
                }
            }

        }
        break;


    case EASY:
        for (int easymine = 0; easymine < width * height * 0.1; easymine++)
        {
            setMines();
        }
        break;

    case NORMAL:
        for (int normalmine = 0; normalmine < width * height * 0.2; normalmine++)
        {
            setMines();
        }
        break;

    case HARD:
        for (int hardmine = 0; hardmine < width * height * 0.3; hardmine++)
        {
            setMines();
        }
        break;
    }

}

void MinesweeperBoard::debug_display() const
{

    for (int wys = 0; wys < height; wys++)
    {
        for (int sz = 0; sz < width; sz++)
        {
            cout << "[";
            if (board[wys][sz].hasMine == 1)
            {
                cout << "M";
            }
            else
            {
                cout << ".";
            }
            if (board[wys][sz].hasFlag == 1)
            {
                cout << "f";
            }
            else
            {
                cout << ".";
            }
            if (board[wys][sz].isRevealed == 1)
            {
                cout << "o";
            }
            else
            {
                cout << ".";
            }
            cout << "]";
        }
        cout << endl;
    }


}
bool MinesweeperBoard::hasMine(int row, int col) const
{
    if (board[row][col].hasMine == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool MinesweeperBoard::isRevealed(int row, int col) const
{
    if (board[row][col].isRevealed == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MinesweeperBoard::isOutside(int row, int col) const
{
    if (row >= 0 && col >= 0 && row <= height && col <= width) {

        return false;
    }
    else
    {
        return true;
    }

}

bool MinesweeperBoard::hasFlag(int row, int col) const
{
    if (board[row][col].hasFlag == 1)
    {
        return true;
    }
    if (board[row][col].hasFlag == 0 || board[row][col].isRevealed == 1)
    {
        return false;
    }
}


void MinesweeperBoard::toggleFlag(int row, int col)
{
    if (isRevealed(row, col) == false && isOutside(row, col) == false)
    {

        if (hasFlag(row, col) == true)
        {
            board[row][col].hasFlag = 0;
        }
        else 
        {
            board[row][col].hasFlag = 1;
        }
    }
    
}
void MinesweeperBoard::revealEmptyFields(int row, int col)
{
    if (isRevealed(row, col) == false && hasFlag(row, col) == false && board[row][col].hasMine == false && isOutside(row, col) == false)
    {
        board[row][col].isRevealed = 1;
    }
}


void MinesweeperBoard::revealField(int row, int col)
{
    if (isRevealed(row, col) == true || isOutside(row, col) == true || hasFlag(row, col) == 1 || state == FINISHED_WIN || state == FINISHED_LOSS)
    {
        return;
    }
    if (isRevealed(row, col) == false && board[row][col].hasMine == 0)
    {
        board[row][col].isRevealed = 1;
        if (FirstMove == true)
        {
            FirstMove = false;
        }
        if (countMines(row, col) == 0)
        {
            revealField(row - 1, col - 1);
            revealField(row - 1, col);
            revealField(row - 1, col + 1);
            revealField(row + 1, col - 1);
            revealField(row + 1, col);
            revealField(row + 1, col + 1);
            revealField(row, col - 1);
            revealField(row, col);
            revealField(row, col + 1);
        }

    }

    if (isRevealed(row, col) == false && board[row][col].hasMine == 1)
    {
        if (FirstMove == true)
        {
            board[row][col].isRevealed = 1;
            board[row][col].hasMine = 0;
            setMines();
            FirstMove = false;
        }
        else
        {
            board[row][col].isRevealed = 1;
            getGameState();
        }
    }
}

int MinesweeperBoard::countMines(int row, int col) const
{
    const_cast<int&>(minecount) = 0; 
    if (isRevealed(row, col) == false || isOutside(row, col) == true)
    {
        return -1;
    }
    else
    {
        for (int wys = -1; wys < 2; wys++)
        {
            for (int szer = -1; szer < 2; szer++)
            {
                if (isOutside(row + szer, col + wys) == false)
                {
                    if (board[row + szer][col + wys].hasMine == true)
                    {
                        const_cast<int&>(minecount)++; 
                    }
                }
            }
        }
        
    }
    return minecount;
}

char MinesweeperBoard::getFieldInfo(int row, int col) const
{
    if (isOutside(row, col) == true)
    {
        return '#';
    }

    if (isRevealed(row, col) == false && hasFlag(row, col) == true)
    {
        return 'F';
    }
    if (isRevealed(row, col) == false && hasFlag(row, col) == false)
    {
        return '_';
    }

    if (isRevealed(row, col) == true && board[row][col].hasMine == 1)
    {
        return 'x';
    }


    if (isRevealed(row, col) == true && countMines(row, col) == 0)
    {
        return ' ';
    }

    if (isRevealed(row, col) == true && countMines(row, col) != 0)
    {
        return countMines(row, col);
    }

}

void  MinesweeperBoard::setMines()
{
 

    int x = rand() % width;
    int y = rand() % height;
    if (board[y][x].hasMine == 1)
    {
        setMines();
    }
    else
    {
        board[y][x].hasMine = 1;
    }
}

GameState MinesweeperBoard::getGameState() const
{
    int revealedUnmined = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (isRevealed(i, j) == true && board[i][j].hasMine == true)
            {
                break;
            }
            if (isRevealed(i, j) == true && board[i][j].hasMine == false)
            {
                revealedUnmined++;
            }
        }
    }
    if (revealedUnmined == (width * width) - ((height * width) * 0.1) && tryb == EASY)
    {
        return FINISHED_WIN;
        cout << "WYGRANA" << endl;
    }
    else 
    {
        for ( int liczy = 0;liczy < width; liczy++)
        {
            for (int liczx = 0; liczx < width; liczx++)
            {
                if (isRevealed(liczy, liczx) == true && hasMine(liczy, liczx) == true)
                {
                    return FINISHED_LOSS;
                    cout << "PRZEGRANA" << endl;
                }
            }

        }
        return RUNNING;
    }
    if (revealedUnmined == (width * width) - ((height * width) * 0.2) && tryb == NORMAL)
    {
        return FINISHED_WIN;
        cout << "WYGRANA" << endl;
    }
    else
    {
        for (int liczy = 0; liczy < width; liczy++)
        {
            for (int liczx = 0; liczx < width; liczx++)
            {
                if (isRevealed(liczy, liczx) == true && hasMine(liczy, liczx) == true)
                {
                    return FINISHED_LOSS;
                    cout << "PRZEGRANA" << endl;
                }
            }

        }
        return RUNNING;
    }
    if (revealedUnmined == (width * width) - ((height * width) * 0.3) && tryb == HARD)
    {
        return FINISHED_WIN;
        cout << "WYGRANA" << endl;
    }
    else
    {
        for (int liczy = 0; liczy < width; liczy++)
        {
            for (int liczx = 0; liczx < width; liczx++)
            {
                if (isRevealed(liczy, liczx) == true && hasMine(liczy, liczx) == true)
                {
                    return FINISHED_LOSS;
                    cout << "PRZEGRANA" << endl;
                }
            }

        }
        return RUNNING;
    }
   
}

void MinesweeperBoard::AllField()
{
    for (int liczy = 0; liczy < width; liczy++)
    {
        for (int liczx = 0; liczx < width; liczx++)
        {
            board[liczy][liczx].isRevealed = 1;
        }

    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return height;
}

int MinesweeperBoard::getMineCount() const
{
    return minecount;
}

