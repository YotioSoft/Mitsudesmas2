#include <LoadFiles.h>

std::map<String, std::map<String, Array<Character>>> LoadFiles::InitCharacters() {
	std::map<String, std::map<String, Array<Character>>>  characters;

	characters[U"man"][U"player"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/man/player/1.png"), Direction::BOTTOM, true);
	
	for (int i=1; i<=16; i++) {
		characters[U"man"][U"youth"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/man/youth/" + Format(i) + U".png"), Direction::RIGHT, false);
	}
	for (int i=1; i<=20; i++) {
		characters[U"man"][U"normal"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/man/normal/" + Format(i) + U".png"), Direction::RIGHT, false);
	}
	
	for (int i=1; i<=5; i++) {
		characters[U"man"][U"solo"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/man/middle_aged/" + Format(i) + U".png"), Direction::BOTTOM, false);
	}
	for (int i=1; i<=20; i++) {
		characters[U"man"][U"solo"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/man/normal/" + Format(i) + U".png"), Direction::BOTTOM, false);
	}
	
	for (int i=1; i<=17; i++) {
		characters[U"woman"][U"youth"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/woman/youth/" + Format(i) + U".png"), Direction::LEFT, false);
	}
	for (int i=1; i<=27; i++) {
		characters[U"woman"][U"normal"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/woman/normal/" + Format(i) + U".png"), Direction::LEFT, false);
	}
	
	for (int i=1; i<=2; i++) {
		characters[U"woman"][U"solo"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/woman/middle_aged/" + Format(i) + U".png"), Direction::BOTTOM, false);
	}
	for (int i=1; i<=27; i++) {
		characters[U"woman"][U"solo"] << Character(Image(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/woman/normal/" + Format(i) + U".png"), Direction::BOTTOM, false);
	}

	return characters;
}

std::map<String, MapObject> LoadFiles::InitMapObjects() {
	std::map<String, MapObject> map_objects;
	Image st_map_e01_original = Image(Unicode::Widen(CURRENT_DIR) + U"/img/map/chips/ST-Map-E01_customed.png");
	Image st_map_e01 = ImageTools::zoomImage2x(st_map_e01_original);
	Image pipo_map_original = Image(Unicode::Widen(CURRENT_DIR) + U"/img/map/chips/pipo-map001.png");
	Image pipo_map = ImageTools::zoomImage2x(pipo_map_original);
	Image base_map_original = Image(Unicode::Widen(CURRENT_DIR) + U"/img/map/chips/mapchip320x240.png");
	Image base_map = ImageTools::zoomImage4x(base_map_original);
	Image base_snow_map_original = Image(Unicode::Widen(CURRENT_DIR) + U"/img/map/chips/base_snow.png");
	Image base_snow_map = ImageTools::zoomImage4x(base_snow_map_original);

	// ’n–Ê
	map_objects[U"grass"] = MapObject(U"grass", MapChipProfiles::Ground);
	map_objects[U"grass"].addMapChip(MapChip(pipo_map, 0, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	
	map_objects[U"snow"] = MapObject(U"snow", MapChipProfiles::Ground);
	map_objects[U"snow"].addMapChip(MapChip(base_snow_map, 8, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));

	// “¹
	map_objects[U"gravel_road"] = MapObject(U"gravel_road", MapChipProfiles::Road);
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 16, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottom, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 17, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 18, MapChipProfiles::Types::Road, MapChipProfiles::Directions::BottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 24, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottom, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 25, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 26, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopBottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 32, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRight, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 33, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 34, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 40, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Vertical, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(st_map_e01, 48, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Horizontal, true));

	map_objects[U"concrete_road"] = MapObject(U"concrete_road", MapChipProfiles::Road);
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 19, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottom, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 20, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 21, MapChipProfiles::Types::Road, MapChipProfiles::Directions::BottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 27, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottom, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 28, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 29, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopBottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 35, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRight, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 36, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 37, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 43, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Vertical, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(st_map_e01, 51, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Horizontal, true));
	
	// –Ø
	map_objects[U"green_tree"] = MapObject(U"green_tree", MapChipProfiles::Tree);
	map_objects[U"green_tree"].addMapChip(MapChip(st_map_e01, 46, MapChipProfiles::Tree, MapChipProfiles::Directions::None, false));
	
	map_objects[U"green_trees"] = MapObject(U"green_trees", MapChipProfiles::Tree);
	map_objects[U"green_trees"].addMapChip(MapChip(st_map_e01, 47, MapChipProfiles::Tree, MapChipProfiles::Directions::None, false));
	
	map_objects[U"snow_tree"] = MapObject(U"snow_tree", MapChipProfiles::Tree);
	map_objects[U"snow_tree"].addMapChip(MapChip(st_map_e01, 54, MapChipProfiles::Tree, MapChipProfiles::Directions::None, false));
	
	map_objects[U"snow_trees"] = MapObject(U"snow_trees", MapChipProfiles::Tree);
	map_objects[U"snow_trees"].addMapChip(MapChip(st_map_e01, 55, MapChipProfiles::Tree, MapChipProfiles::Directions::None, false));
	
	map_objects[U"big_tree"] = MapObject(U"big_tree", MapChipProfiles::ExpandableTree);
	map_objects[U"big_tree"].setObjectSize(Size (2, 2));
	map_objects[U"big_tree"].addMapChip(MapChip(base_map, 48, MapChipProfiles::ExpandableTree, MapChipProfiles::Directions::RightBottom, false));
	map_objects[U"big_tree"].addMapChip(MapChip(base_map, 49, MapChipProfiles::ExpandableTree, MapChipProfiles::Directions::BottomLeft, false));
	map_objects[U"big_tree"].addMapChip(MapChip(base_map, 56, MapChipProfiles::ExpandableTree, MapChipProfiles::Directions::TopRight, false));
	map_objects[U"big_tree"].addMapChip(MapChip(base_map, 57, MapChipProfiles::ExpandableTree, MapChipProfiles::Directions::TopLeft, false));
	
	// ŽR
	map_objects[U"green_mountains"] = MapObject(U"green_mountains", MapChipProfiles::Mountain);
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 128, MapChipProfiles::Mountain, MapChipProfiles::Directions::RightBottom, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 129, MapChipProfiles::Mountain, MapChipProfiles::Directions::RightBottomLeft, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 130, MapChipProfiles::Mountain, MapChipProfiles::Directions::BottomLeft, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 136, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightBottom, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 137, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightBottomLeft, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 138, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopBottomLeft, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 144, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRight, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 145, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightLeft, false));
	map_objects[U"green_mountains"].addMapChip(MapChip(st_map_e01, 146, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopLeft, false));
	
	map_objects[U"snow_mountains"] = MapObject(U"snow_mountains", MapChipProfiles::Mountain);
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 155, MapChipProfiles::Mountain, MapChipProfiles::Directions::RightBottom, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 156, MapChipProfiles::Mountain, MapChipProfiles::Directions::RightBottomLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 157, MapChipProfiles::Mountain, MapChipProfiles::Directions::BottomLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 163, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightBottom, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 164, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightBottomLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 165, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopBottomLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 171, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRight, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 172, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 173, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 206, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleRightBottom, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 207, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleBottomLeft, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 214, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleTopRight, false));
	map_objects[U"snow_mountains"].addMapChip(MapChip(st_map_e01, 215, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleTopLeft, false));
	
	map_objects[U"rock_mountains"] = MapObject(U"rock_mountains", MapChipProfiles::Mountain);
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 176, MapChipProfiles::Mountain, MapChipProfiles::Directions::RightBottom, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 177, MapChipProfiles::Mountain, MapChipProfiles::Directions::RightBottomLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 178, MapChipProfiles::Mountain, MapChipProfiles::Directions::BottomLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 184, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightBottom, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 185, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightBottomLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 186, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopBottomLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 192, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRight, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 193, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopRightLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 194, MapChipProfiles::Mountain, MapChipProfiles::Directions::TopLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 206, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleRightBottom, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 207, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleBottomLeft, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 214, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleTopRight, false));
	map_objects[U"rock_mountains"].addMapChip(MapChip(st_map_e01, 215, MapChipProfiles::Mountain, MapChipProfiles::Directions::CircleTopLeft, false));
	
	// Œš•¨
	map_objects[U"school"] = MapObject(U"school", MapChipProfiles::Building);
	map_objects[U"school"].addMapChip(MapChip(st_map_e01, 200, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	map_objects[U"store1"] = MapObject(U"store1", MapChipProfiles::Building);
	map_objects[U"store1"].addMapChip(MapChip(st_map_e01, 201, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	map_objects[U"store2"] = MapObject(U"store2", MapChipProfiles::Building);
	map_objects[U"store2"].addMapChip(MapChip(st_map_e01, 202, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	map_objects[U"house1"] = MapObject(U"house1", MapChipProfiles::Building);
	map_objects[U"house1"].addMapChip(MapChip(st_map_e01, 203, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	map_objects[U"house2"] = MapObject(U"house2", MapChipProfiles::Building);
	map_objects[U"house2"].addMapChip(MapChip(st_map_e01, 204, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	map_objects[U"house3"] = MapObject(U"house3", MapChipProfiles::Building);
	map_objects[U"house3"].addMapChip(MapChip(st_map_e01, 205, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	map_objects[U"house4"] = MapObject(U"house4", MapChipProfiles::Building);
	map_objects[U"house4"].addMapChip(MapChip(st_map_e01, 211, MapChipProfiles::Building, MapChipProfiles::Directions::None, false));
	
	//map_objects

	return map_objects;
}

