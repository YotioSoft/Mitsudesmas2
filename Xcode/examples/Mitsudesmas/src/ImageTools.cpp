#include "ImageTools.h"

Image ImageTools::zoomImage2x(Image& original) {
	Image resized_image(original.width() * 2, original.height() * 2);

	for (int y = 0; y < original.height(); y++) {
		for (int x = 0; x < original.width(); x++) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					resized_image[y * 2 + i][x * 2 + j] = original[y][x];
				}
			}
		}
	}

	return resized_image;
}

Image ImageTools::zoomImage4x(Image& original) {
	Image resized_image(original.width() * 4, original.height() * 4);

	for (int y = 0; y < original.height(); y++) {
		for (int x = 0; x < original.width(); x++) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					resized_image[y * 4 + i][x * 4 + j] = original[y][x];
				}
			}
		}
	}

	return resized_image;
}

Point ImageTools::getObjectPositionOnImage(const int number, const Size chip_size, const int chips_in_a_row) {
	int x = number % chips_in_a_row * chip_size.x;
	int y = number / chips_in_a_row * chip_size.y;

	return Point(x, y);
}
