#pragma once

#include <Siv3D.hpp> // OpenSiv3D v0.6.6

#define CHIP_SIZE		Size(64, 64)
#define CHIPS_IN_A_ROW	8
#if defined(_WIN32) || defined(_WIN64)
	#define CURRENT_DIR     "./"
#else
	#define CURRENT_DIR     "./Mitsudesmas2.app/Contents/Resources"
#endif

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
	static Point TOP	= Point(0, -16);
	static Point LEFT	= Point(-16, 0);
	static Point BOTTOM	= Point(0, 16);
	static Point RIGHT	= Point(16, 0);
}

namespace Result {
	const static int SUCCESS	= 1;
	const static int FAILURE	= 2;
	const static int NONE		= 3;
}
