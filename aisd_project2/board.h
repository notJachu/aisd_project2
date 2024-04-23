#pragma once
#include "data_types.h"
#include <string>

class Board {
private:
	FIELD board[11][11];
	int size;
	int getNextState(std::string input, int row);
	void read_board();

public:
	Board(int size);
	~Board();

	void print_board() const;
	void setFieldState(int x, int y, FIELD_STATE state);
	FIELD_STATE getFieldState(int x, int y);
	void setConnection(int x, int y, int direction, bool value);
	bool getConnection(int x, int y, int direction);
	int getSize();
};