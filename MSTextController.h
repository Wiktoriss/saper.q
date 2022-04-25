#pragma once
#include "MSBoardTextView.h"
#include "MinesweeperBoard.h"
class MSTextController :
    public MinesweeperBoard
{
    MinesweeperBoard& board;
    MSBoardTextView& view;
public:
    MSTextController(MinesweeperBoard& board2, MSBoardTextView& view2);
    void play();
    int getX();
    int getY(); 
    int Win();
};