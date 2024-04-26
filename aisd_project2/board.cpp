#include "board.h"
#include <iostream>
#include <string>


void Board::read_board() {
	std::string input;
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; i++) {
		x = i;
		y = 0;
		int index = 0;
		getline(std::cin, input);
		do {
			//logic for parsing input
			while (input[index] != '<') {
				index++;
			}

			index += 2; // offset to letter
			char state = input[index]; 
			if (state == 'r') {
				board[x][y] = RED;
				red++;
			}
			else if (state == 'b') {
				board[x][y] = BLUE;
				blue++;
			}
			else {
				board[x][y] = EMPTY;
			}
			//std::cout << x << " " << y << std::endl;
			x--;
			y++;
		} while (y <= i);
	}
	for (int i = 1; i < size; i++) {
		y = i;
		x = size - 1;
		int index = 0;
		getline(std::cin, input);
		do {
			//logic for parsing input
			while (input[index] != '<') {
				index++;
			}

			index += 2; // offset to letter
			char state = input[index]; 
			if (state == 'r') {
				board[x][y] = RED;
				red++;
			}
			else if (state == 'b') {
				board[x][y] = BLUE;
				blue++;
			}
			else {
				board[x][y] = EMPTY;
			}
			//std::cout << x << " " << y << std::endl;
			x--;
			y++;
		} while (y < size);
	}
	getline(std::cin, input); // to get rid of the empty line

}

void Board::reset_visited() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			visited[i][j] = false;
		}
	}
}

void Board::reset_win_counter() {
	this->win_counter = 0;
}

void Board::setTraverseMode(bool mode) {
	this->traverse_mode = mode;
}

void Board::traverse(Point start, FIELD_STATE state) {

	// firse validate if position is possible
	// if not return

	if (start.x < 0 || start.y < 0 || start.x >= size || start.y >= size) {
		return;
	}

	if (visited[start.x][start.y] != traverse_mode) {
		return;
	}

	if (board[start.x][start.y] != state) {
		return;
	}

	visited[start.x][start.y] = !traverse_mode;
	removed[start.x][start.y] = !add_back;

	switch (state) {
	case EMPTY:
		break;
	case RED:
		if (start.y == 0) {
			reached_top++;
			//if (size > 2) return;			// for boards smaller that 3x3 it breaks
		}
		if (start.y == size - 1) {
			reached_bottom++;
			//if (size > 2) return;			// for boards smaller that 3x3 it breaks
		}
		break;
	case BLUE:
		if (start.x == 0) {
			reached_top++;
			//if (size > 2) return;			// for boards smaller that 3x3 it breaks
		}
		if (start.x == size - 1) {
			reached_bottom++;
			//if (size > 2) return;			// for boards smaller that 3x3 it breaks
		}
		break;
	default:
		break;
	}


	// LEFT
		traverse({ start.x - 1, start.y }, state);

	// RIGHT
		traverse({ start.x + 1, start.y }, state);

	// UP
		traverse({ start.x, start.y - 1 }, state);

	// DOWN
		traverse({ start.x, start.y + 1 }, state);

	// UP LEFT
		traverse({ start.x - 1, start.y - 1 }, state);

	// DOWN RIGHT
		traverse({ start.x + 1, start.y + 1 }, state);

	return;
}

void Board::check_with_removed(Point start, FIELD_STATE state) {
														
	// its pretty much the same as traverse but with extra if


	visited[start.x][start.y] = !traverse_mode;
	is_board_possible = false;

	bool local_reached_top[6] = { false, false, false, false, false, false };
	bool local_reached_bottom[6] = { false, false, false, false, false, false };
										  
	// LEFT
	reached_bottom = 0;
	reached_top = 0;
	traverse({ start.x - 1, start.y }, state);
	if (reached_bottom > 0) {
		local_reached_bottom[0] = true;
	}
	if (reached_top > 0) {
		local_reached_top[0] = true;
	}


	// RIGHT
	reached_bottom = 0;
	reached_top = 0;
	traverse({ start.x + 1, start.y }, state);
	if (reached_bottom > 0) {
		local_reached_bottom[1] = true;
	}
	if (reached_top > 0) {
		local_reached_top[1] = true;
	}

	// UP
	reached_bottom = 0;
	reached_top = 0;
	traverse({ start.x, start.y - 1 }, state);
	if (reached_bottom > 0) {
		local_reached_bottom[2] = true;
	}
	if (reached_top > 0) {
		local_reached_top[2] = true;
	}

	// DOWN
	reached_bottom = 0;
	reached_top = 0;
	traverse({ start.x, start.y + 1 }, state);
	if (reached_bottom > 0) {
		local_reached_bottom[3] = true;
	}
	if (reached_top > 0) {
		local_reached_top[3] = true;
	}

	// UP LEFT
	reached_bottom = 0;
	reached_top = 0;
	traverse({ start.x - 1, start.y - 1 }, state);
	if (reached_bottom > 0) {
		local_reached_bottom[4] = true;
	}
	if (reached_top > 0) {
		local_reached_top[4] = true;
	}

	// DOWN RIGHT
	reached_bottom = 0;
	reached_top = 0;
	traverse({ start.x + 1, start.y + 1 }, state);
	if (reached_bottom > 0) {
		local_reached_bottom[5] = true;
	}
	if (reached_top > 0) {
		local_reached_top[5] = true;
	}


	for (int i = 0; i < 6; i++) {
		if (local_reached_bottom[i] && local_reached_top[i]) {
			is_board_possible = false;
			traverse_mode = false;
			return;
		}
	}

   is_board_possible = true;

}


Board::Board(int size) {
	this->size = size;
	this->red = 0;
	this->blue = 0;
	this->win_counter = 0;
	this->traverse_mode = false;
	this->add_back = false;
	reset_visited();
	read_board();
}

Board::~Board()
{
}

void Board::print_board() const {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == RED) {
				std::cout << "r ";
			}
			else if (board[i][j] == BLUE) {
				std::cout << "b ";
			}
			else {
				std::cout << "e ";
			}
		}
		std::cout << std::endl;
	}
}

void Board::setFieldState(int x, int y, FIELD_STATE state)
{
}

FIELD_STATE Board::getFieldState(int x, int y)
{
	return FIELD_STATE();
}

void Board::setConnection(int x, int y, int direction, bool value)
{
}

bool Board::getConnection(int x, int y, int direction)
{
	return false;
}

bool Board::isBoardCorrect() {
	if (red == blue) {
		return true;
	}
	else if (red - blue == 1) {
		return true;
	}

	return false;
}

FIELD_STATE Board::isGameOver() {
	// first check red player then blue

	if (!isBoardCorrect()) {
		//std::cout << "NO" << std::endl;
		return EMPTY;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			removed[i][j] = false;
		}
	}

	reached_bottom = 0;
	reached_top = 0;

	int red_wins = 0;
	int blue_wins = 0;

	bool first_on_path = true;

	FIELD_STATE weak_winner = EMPTY;	  // won but board is not possible

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			traverse_mode = false;
			reached_bottom = 0;
			reached_top = 0;
			reset_visited();
			if (board[i][j] != EMPTY) {
				
				if (board[i][j] == weak_winner && win_counter > 0) {
					 first_on_path = !removed[i][j];
				}
				traverse({ i, j }, board[i][j]);
				if (reached_bottom == 1 && reached_top == 1) {

					weak_winner = board[i][j];
					if (!first_on_path) {
						continue;
					}
					first_on_path = false;
					if (board[i][j] == RED) {
						red_wins++;
					}
					else {
						blue_wins++;
					}
					win_counter++;
				}
				else if (reached_bottom >= 1 && reached_top >= 1) {
					weak_winner = board[i][j];
					traverse_mode = true;
					check_with_removed({ i, j }, board[i][j]);
					
					if (!first_on_path) {
						continue;
					}
					if (is_board_possible) {
						first_on_path = false;
						if (board[i][j] == RED) {
							red_wins++;
						}
						else {
							blue_wins++;
						}
						win_counter++;
					}
					else {
						add_back = true;
						traverse({ i, j }, board[i][j]);
						add_back = false;
					}
				}
			}
		}
	}

	if (weak_winner != EMPTY && win_counter == 0) {
		win_counter = 10;						   // random value to accout for invalid path (2 joined paths won't be counted)
	}
	return weak_winner;

	if (red_wins == 0 && blue_wins == 0) {
		//std::cout << "NO" << std::endl;
		return EMPTY;
	}
	else if (win_counter > 1) {
		//std::cout << "NO" << std::endl;
		return EMPTY;
	}
	else if (red_wins > 0) {
		//std::cout << "YES RED" << std::endl;
		return RED;
	}
	else {
		//std::cout << "YES BLUE" << std::endl;
		return BLUE;
	}

}

bool Board::isBoardPossible() {
	this->win_counter = 0;
	if (!isBoardCorrect()) return false;

	FIELD_STATE winner = isGameOver();

	switch (winner)
	{
	case EMPTY:
		break;
	case RED:
		if (red - 1 != blue)
			return false;
		break;
	case BLUE:
		if (red != blue)
			return false;
		break;
	default:
		break;
	}

	reset_visited();
	return win_counter <= 1;
}

int Board::getSize() {
	return this->size;
}

int Board::getBlue() {
	return this->blue;
}

int Board::getRed() {
	return this->red;
}
