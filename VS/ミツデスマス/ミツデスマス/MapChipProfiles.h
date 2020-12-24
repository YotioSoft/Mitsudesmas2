#pragma once

namespace MapChipProfiles {
	enum Types {
		Road = 1,
		Wall = 2,
		Ground = 3,
		WaterSurface = 4,
		Tree = 5,
		Mountain = 6,
		Building = 7,
		ExpandableTree = 8
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
		Horizontal			= 11,
		CircleTopRight		= 12,
		CircleRightBottom	= 13,
		CircleBottomLeft	= 14,
		CircleTopLeft		= 15
	};

	Directions convertIntToDirections(int number);
}
