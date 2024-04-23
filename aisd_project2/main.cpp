#include <stdio.h>
#include "data_types.h"

using namespace std;

int main() {
	/*CONNECTION_LIST connections{};
	for (int i = 0; i < 6; i++) {
		connections[i] = false;
	}

	connections[UP] = true;

	printf("UP: %d\n", connections[UP]);*/

	int count = 0;
	char in;
	do {
		in = getchar();
		count++;
	} while (in != '-');
	int size = ((count - 1) / 3) + 1;
	printf("Size: %d\n", size);
	return 0;
}