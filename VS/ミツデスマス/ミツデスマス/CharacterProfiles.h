#pragma once
#include "header.h"

namespace character_profiles {
	const static int backward_1 = 0;
	const static int backward_2 = 1;
	const static int backward_3 = 2;

	const static int left_1 = 3;
	const static int left_2 = 4;
	const static int left_3 = 5;

	const static int right_1 = 6;
	const static int right_2 = 7;
	const static int right_3 = 8;

	const static int forward_1 = 9;
	const static int forward_2 = 10;
	const static int forward_3 = 11;

	const static int direction_backward = 0;
	const static int direction_left = 1;
	const static int direction_right = 2;
	const static int direction_forward = 3;

	const static RectF pos_on_image[12] = {
		RectF(0, 0, 64, 64), RectF(64, 0, 64, 64), RectF(128, 0, 64, 64),
		RectF(0, 64, 64, 64), RectF(64, 64, 64, 64), RectF(128, 64, 64, 64),
		RectF(0, 128, 64, 64), RectF(64, 128, 64, 64), RectF(128, 128, 64, 64),
		RectF(0, 192, 64, 64), RectF(64, 192, 64, 64), RectF(128, 192, 64, 64)
	};
}
