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

bool Board::traverse(Point start, FIELD_STATE state, Point target) {
	// ignoring x or y according to player
	// using -1 as flag

	if (target.x == -1) {
		if (target.y == start.y) {
			return true;
		}
	}
	else if (target.y == -1) {
		if (target.x == start.x) {
			return true;
		}
	}

	visited[start.x][start.y] = true;

	// LEFT
	if (start.x - 1 >= 0 && board[start.x - 1][start.y] == state && !visited[start.x - 1][start.y]) {
		visited[start.x - 1][start.y] = true;
		if (traverse({ start.x - 1, start.y }, state, target)) {
			return true;
		}
	}

	// RIGHT
	if (start.x + 1 < size && board[start.x + 1][start.y] == state && !visited[start.x + 1][start.y]) {
		visited[start.x + 1][start.y] = true;
		if (traverse({ start.x + 1, start.y }, state, target)) {
			return true;
		}
	}

	// UP
	if (start.y - 1 >= 0 && board[start.x][start.y - 1] == state && !visited[start.x][start.y - 1]) {
		visited[start.x][start.y - 1] = true;
		if (traverse({ start.x, start.y - 1 }, state, target)) {
			return true;
		}
	}

	// DOWN
	if (start.y + 1 < size && board[start.x][start.y + 1] == state && !visited[start.x][start.y + 1]) {
		visited[start.x][start.y + 1] = true;
		if (traverse({ start.x, start.y + 1 }, state, target)) {
			return true;
		}
	}

	// UP LEFT
	if (start.x - 1 >= 0 && start.y - 1 >= 0 && board[start.x - 1][start.y - 1] == state && !visited[start.x - 1][start.y - 1]) {
		visited[start.x - 1][start.y - 1] = true;
		if (traverse({ start.x - 1, start.y - 1 }, state, target)) {
			return true;
		}
	}

	// DOWN RIGHT
	if (start.x + 1 < size && start.y + 1 < size && board[start.x + 1][start.y + 1] == state && !visited[start.x + 1][start.y + 1]) {
		visited[start.x + 1][start.y + 1] = true;
		if (traverse({ start.x + 1, start.y + 1 }, state, target)) {
			return true;
		}
	}

	return false;
}


Board::Board(int size) {
	this->size = size;
	this->red = 0;
	this->blue = 0;
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

bool Board::isGameOver() {
	// first check red player then blue

	if (!isBoardCorrect()) {
		std::cout << "NO" << std::endl;
		return false;
	}

	for (int i = 0; i < size; i++) {

		// RED
		if (board[i][0] == RED && !visited[i][0]) {
			if (traverse({ i, 0 }, RED, { -1, size - 1 })) {
				std::cout << "YES RED" << std::endl;
				return true;
			}
		}
		if (board[i][size - 1] == RED && !visited[i][size - 1]) {
			if (traverse({ i, size - 1 }, RED, { -1, 0 })) {
				std::cout << "YES RED" << std::endl;
				return true;
			}
		}

		// BLUE
		if (board[0][i] == BLUE && !visited[0][i]) {
			if (traverse({ 0, i }, BLUE, { size - 1, -1 })) {
				std::cout << "YES BLUE" << std::endl;
				return true;
			}
		}
		if (board[size - 1][i] == BLUE && !visited[size - 1][i]) {
			if (traverse({ size - 1, i }, BLUE, { 0, -1 })) {
				std::cout << "YES BLUE" << std::endl;
				return true;
			}
		}

	}
	std::cout << "NO" << std::endl;
	return false;
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
