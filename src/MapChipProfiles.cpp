#include <MapChipProfiles.h>

MapChipProfiles::Directions MapChipProfiles::convertIntToDirections(int number) {
	switch (number) {
	case 1:
		return Directions::RightBottom;
	case 2:
		return Directions::RightBottomLeft;
	case 3:
		return Directions::BottomLeft;
	case 4:
		return Directions::TopRightBottom;
	case 5:
		return Directions::TopRightBottomLeft;
	case 6:
		return Directions::TopBottomLeft;
	case 7:
		return Directions::TopRight;
	case 8:
		return Directions::TopRightLeft;
	case 9:
		return Directions::TopLeft;
	case 10:
		return Directions::Vertical;
	case 11:
		return Directions::Horizontal;
	default:
		return Directions::None;
	}
}
