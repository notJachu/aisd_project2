#pragma once
#include "data_types.h"

class Board {
private:
	FIELD board[11][11];
	int size;

public:
	Board(int size);
	~Board();

	void setFieldState(int x, int y, FIELD_STATE state);
	FIELD_STATE getFieldState(int x, int y);
	void setConnection(int x, int y, int direction, bool value);
	bool getConnection(int x, int y, int direction);
	int getSize();
};