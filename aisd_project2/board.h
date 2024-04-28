#pragma once
#include "data_types.h"
#include <string>

class Board {
private:
	FIELD_STATE board[11][11];
	bool visited[11][11];
	bool removed[11][11];
	int size;
	int red;
	int blue;
	void read_board(); 
	void traverse(Point start, FIELD_STATE state);
	void check_with_removed(Point start, FIELD_STATE state);
	int win_counter;
	bool traverse_mode; // true - chcecking visited, false - checking not visited
	int reached_top;
	int reached_bottom;
	bool is_board_possible;
	bool add_back;		// flag for adding back to removed when path was not added

public:
	Board(int size);
	~Board();

	void print_board() const;
	void setFieldState(int x, int y, FIELD_STATE state);
	FIELD_STATE getFieldState(int x, int y);
	void setConnection(int x, int y, int direction, bool value);
	bool getConnection(int x, int y, int direction);
	void reset_visited();
	void reset_win_counter();
	void setTraverseMode(bool mode);
	bool isBoardCorrect();
	FIELD_STATE isGameOver(); // reusing enum to tell who won EMPTY == NO
	bool isBoardPossible();
	bool check_util(Point offset, FIELD_STATE player, int moves);
	bool chceckAdjecent(Point start, FIELD_STATE state, int moves);
	bool canWinNaive(int moves, FIELD_STATE player);
	int getSize();
	int getRed();
	int getBlue();
};