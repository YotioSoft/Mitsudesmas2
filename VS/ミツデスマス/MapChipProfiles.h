#pragma once

namespace MapChipProfiles {
	enum Types {
		Road = 1,
		Wall = 2,
		Ground = 3,
		WaterSurface = 4,
	};

	enum Directions {
		None				= 0,
		RightBottom			= 1,
		RightBottomLeft		= 2,
		BottomLeft			= 3,
		TopRightBottom		= 4,
		TopRightBottomLeft	= 5,
		TopBottomLeft		= 6,
		TopRight			= 7,
		TopRightLeft		= 8,
		TopLeft				= 9,
		Vertical			= 10,
		Horizontal			= 11
	};

	Directions convertIntToDirections(int number);
}
