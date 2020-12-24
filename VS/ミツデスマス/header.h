#pragma once

#include <Siv3D.hpp> // OpenSiv3D v0.4.3

#define CHIP_SIZE		Size(64, 64)
#define CHIPS_IN_A_ROW	8

typedef struct SquarePosition {
	int x;
	int y;

	SquarePosition() {}
	SquarePosition(int init_x, int init_y) {
		x = init_x;
		y = init_y;
	}
} SquarePosition;

namespace Direction {
	const static Point TOP		= Point(0, -8);
	const static Point LEFT		= Point(-8, 0);
	const static Point BOTTOM	= Point(0, 8);
	const static Point RIGHT	= Point(8, 0);
}
