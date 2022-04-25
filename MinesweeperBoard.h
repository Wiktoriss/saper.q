#pragma once
#pragma once
#ifndef MINESBOARD_H__
#define MINESBOARD_H__



enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
	bool hasMine;
	bool hasFlag;
	bool isRevealed;
};

class MinesweeperBoard
{
	Field board[100][100];
	int width;
	int height;
	GameState state;
	GameMode tryb;
	bool FirstMove;

public:
	int	minecount;
	MinesweeperBoard();
	MinesweeperBoard(int width, int height, GameMode mode);
	void setMines();
	int getBoardWidth() const;
	int getBoardHeight() const;
	int getMineCount() const;
	bool isOutside(int row, int col) const;
	int countMines(int row, int col) const;
	bool hasFlag(int row, int col) const; 
	void toggleFlag(int row, int col);
	void revealField(int row, int col); 
	bool isRevealed(int row, int col) const; 
	GameState getGameState() const;
	char getFieldInfo(int row, int col) const;
	void debug_display() const;
	int getPlayerMove() const;
	void revealEmptyFields(int row, int col);
	bool hasMine(int row, int col) const;
	void AllField();
};

#endif