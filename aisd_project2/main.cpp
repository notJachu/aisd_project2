#include <stdio.h>
#include <iostream>
#include <string>
#include "data_types.h"
#include "board.h"

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
			board->isGameOver();
		}

	}
	

	return 0;
}