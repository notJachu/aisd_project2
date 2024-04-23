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
				board[x][y].state = RED;
				red++;
			}
			else if (state == 'b') {
				board[x][y].state = BLUE;
				blue++;
			}
			else {
				board[x][y].state = EMPTY;
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
				board[x][y].state = RED;
				red++;
			}
			else if (state == 'b') {
				board[x][y].state = BLUE;
				blue++;
			}
			else {
				board[x][y].state = EMPTY;
			}
			//std::cout << x << " " << y << std::endl;
			x--;
			y++;
		} while (y < size);
	}
	getline(std::cin, input); // to get rid of the empty line

}


Board::Board(int size) {
	this->size = size;
	this->red = 0;
	this->blue = 0;
	read_board();
}

Board::~Board()
{
}

void Board::print_board() const {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j].state == RED) {
				std::cout << "r ";
			}
			else if (board[i][j].state == BLUE) {
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

int Board::getSize() {
	return this->size;
}

int Board::getBlue() {
	return this->blue;
}

int Board::getRed() {
	return this->red;
}
