#pragma once

enum FIELD_STATE {
	EMPTY,
	RED,
	BLUE
};

enum DIRECTION {
	DOWN,
	LEFT,
	UP_LEFT,
	UP,
	RIGHT,
	DOWN_RIGHT
};

using CONNECTION_LIST = bool[6];

typedef struct FIELD {
	FIELD_STATE state;
	CONNECTION_LIST connections;
} FIELD;

typedef struct Point {
	int x;
	int y;
} Point;