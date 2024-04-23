#pragma once
#include "data_types.h"
#include <string>

class Board {
private:
	FIELD_STATE board[11][11];
	bool visited[11][11];
	int size;
	int red;
	int blue;
	void read_board();
	void reset_visited();
	bool traverse(Point start, FIELD_STATE state, Point target);


public:
	Board(int size);
	~Board();

	void print_board() const;
	void setFieldState(int x, int y, FIELD_STATE state);
	FIELD_STATE getFieldState(int x, int y);
	void setConnection(int x, int y, int direction, bool value);
	bool getConnection(int x, int y, int direction);
	bool isBoardCorrect();
	bool isGameOver();
	int getSize();
	int getRed();
	int getBlue();
};