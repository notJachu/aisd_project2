#include <stdio.h>
#include <iostream>
#include <string>
#include "data_types.h"
#include "board.h"
#include <fstream>

using namespace std;

int main() {
	/*CONNECTION_LIST connections{};
	for (int i = 0; i < 6; i++) {
		connections[i] = false;
	}

	connections[UP] = true;

	printf("UP: %d\n", connections[UP]);*/

	Board* board = nullptr;
	string input;
	int counter = 1;

	//fstream file;
	//file.open("test2.txt", ios::out);

	while (cin.good()) {
		getline(cin, input);
		if (input[0] == ' ') {
			int size = 0;
			while (input[size] != '-') {
				size++;
			}
			size = ((size - 1) / 3) + 1;
			//cout << "Size: " << size << endl;
			if (board != nullptr) {
				delete board;
				board = nullptr;
			}
			board = new Board(size);
			//board->print_board();
		}
		else if (input[0] == 'B') {
			if (board != nullptr) {
				cout << board->getSize() << endl;
			}
			
		}
		else if (input.compare("PAWNS_NUMBER") == 0) {
			int x = (board->getBlue() + board->getRed());
			cout << x << endl;
		}
		else if (input.compare("IS_BOARD_CORRECT") == 0) {
			board->isBoardCorrect() ? cout << "YES" << endl : cout << "NO" << endl;
		}
		else if (input.compare("IS_GAME_OVER") == 0) {
			board->reset_win_counter();
			switch (board->isGameOver())
			{
			case EMPTY:
				cout << "NO" << endl;
				//file << "NO" << endl;
				break;
			case RED:
				cout << "YES RED" << endl;
				//file << "YES RED" << endl;
				break;
			case BLUE:
				cout << "YES BLUE" << endl;
				//file << "YES BLUE" << endl;
				break;
			default:
				break;
			}
			//file << endl;
			cout << endl;
			board->reset_visited();
		}
		else if (input.compare("IS_BOARD_POSSIBLE") == 0) {
			if (board->isBoardPossible()) {
				cout << "YES" << endl;
				//file << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
				//file << "NO" << endl;
			}
			//file << endl;
		}
		// 15 is offset from end to start of the opponent mode
		else if (input.substr(0, 3) == "CAN" && input[input.length() - 14] == 'N') {
			FIELD_STATE player;
			int moves = 0;
			int offset = 4;	 // CAN_
			if (input[offset] == 'R') {
				player = RED;
				offset += 4; // RED_
			}
			else {
				player = BLUE;
				offset += 5; // BLUE_
			} 

			offset += 7; // WIN_IN_

			moves = int(input[offset]) - 48;  // ASCII to int
			//cout << moves << endl;

			if (board->canWinNaive(moves, player)) {
				cout << "YES" << endl;
				//file << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
				//file << "NO" << endl;
			}
			if (counter == 4) {
				//file << endl;
				cout << endl;
				counter = 0;
			}
			counter++;
			//file << endl;
		}

	}
	
	//file.close();
	return 0;
}