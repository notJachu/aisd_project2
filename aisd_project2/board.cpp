#include "board.h"
#include <iostream>
#include <string>

int Board::getNextState(std::string input, int row) {
	static int index;
	static int current_row;
	if (index == 0) {
		current_row = row;
	}
	else if (current_row != row) {
		index = 0;
		current_row = row;
	}

	while (input[index] != '<') {
		index++;
	}
	index += 2;
	return index;
}

void Board::read_board() {
	std::string input;
	int x = 0;
	int y = 0;
	for (int i = 0; i < size; i++) {
		x = i;
		y = 0;
		getline(std::cin, input);
		do {
			//logic for parsing input
			int index = getNextState(input, i);
			char state = input[index]; 
			if (state == 'r') {
				board[x][y].state = RED;
			}
			else if (state == 'b') {
				board[x][y].state = BLUE;
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
		getline(std::cin, input);
		do {
			//logic for parsing input
			int index = getNextState(input, i);
			char state = input[index]; 
			if (state == 'r') {
				board[x][y].state = RED;
			}
			else if (state == 'b') {
				board[x][y].state = BLUE;
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

int Board::getSize() {
	return this->size;
}
