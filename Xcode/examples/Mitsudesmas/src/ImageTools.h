#pragma once
#include "header.h"

namespace ImageTools {
	// Imageを2倍にする
	Image zoomImage2x(Image& original);
	Image zoomImage4x(Image& original);

	// 番号から画像上の座標に変換
	// 番号は左上から横方向に1つずつ順に割り当てられている
	Point getObjectPositionOnImage(const int number, const Size chip_size, const int chips_in_a_row);
}
