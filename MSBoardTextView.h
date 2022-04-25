#pragma once
#include "MinesweeperBoard.h"
class MSBoardTextView :
    public MinesweeperBoard
{
    MinesweeperBoard& board;

public:
    MSBoardTextView(MinesweeperBoard& board);
    MSBoardTextView(const MSBoardTextView& view2);
    void display() const;
};
