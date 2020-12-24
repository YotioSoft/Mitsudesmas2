#include "LoadFiles.h"

std::map<String, Texture> LoadFiles::InitTextures() {
	std::map<String, Texture> textures;

	textures[U"logo"] = Texture(U"img/logo.png");

	return textures;
}

std::map<String, Character> LoadFiles::InitCharacters() {
	std::map<String, Character> characters;

	characters[U"player"] = Character(Image(U"img/charactors/man/player/1.png"), Direction::BOTTOM, true);

	return characters;
}

std::map<String, MapObject> LoadFiles::InitMapObjects() {
	std::map<String, MapObject> map_objects;
	Image world_map_image = ImageTools::zoomImage2x(Image(U"img/map/chips/ST-Map-E01_customed.png"));

	// ’n–Ê
	map_objects[U"gravel"] = MapObject(U"gravel", MapChipProfiles::Ground);
	map_objects[U"gravel"].addMapChip(MapChip(world_map_image, 0, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"concrete1"] = MapObject(U"concrete1", MapChipProfiles::Ground);
	map_objects[U"concrete1"].addMapChip(MapChip(world_map_image, 1, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"grass"] = MapObject(U"grass", MapChipProfiles::Ground);
	map_objects[U"grass"].addMapChip(MapChip(world_map_image, 2, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"soil"] = MapObject(U"soil", MapChipProfiles::Ground);
	map_objects[U"soil"].addMapChip(MapChip(world_map_image, 3, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"concrete2"] = MapObject(U"concrete2", MapChipProfiles::Ground);
	map_objects[U"concrete2"].addMapChip(MapChip(world_map_image, 9, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"concrete3"] = MapObject(U"concrete3", MapChipProfiles::Ground);
	map_objects[U"concrete3"].addMapChip(MapChip(world_map_image, 10, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"concrete4"] = MapObject(U"concrete4", MapChipProfiles::Ground);
	map_objects[U"concrete4"].addMapChip(MapChip(world_map_image, 11, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));
	map_objects[U"concrete5"] = MapObject(U"concrete5", MapChipProfiles::Ground);
	map_objects[U"concrete5"].addMapChip(MapChip(world_map_image, 12, MapChipProfiles::Types::Ground, MapChipProfiles::Directions::None, true));

	// “¹˜H
	map_objects[U"gravel_road"] = MapObject(U"gravel_road", MapChipProfiles::Road);
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 16, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottom, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 17, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 18, MapChipProfiles::Types::Road, MapChipProfiles::Directions::BottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 24, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottom, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 25, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 26, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopBottomLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 32, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRight, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 33, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 34, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopLeft, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 40, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Vertical, true));
	map_objects[U"gravel_road"].addMapChip(MapChip(world_map_image, 48, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Horizontal, true));

	map_objects[U"concrete_road"] = MapObject(U"concrete_road", MapChipProfiles::Road);
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 19, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottom, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 20, MapChipProfiles::Types::Road, MapChipProfiles::Directions::RightBottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 21, MapChipProfiles::Types::Road, MapChipProfiles::Directions::BottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 27, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottom, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 28, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightBottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 29, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopBottomLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 35, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRight, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 36, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopRightLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 37, MapChipProfiles::Types::Road, MapChipProfiles::Directions::TopLeft, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 43, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Vertical, true));
	map_objects[U"concrete_road"].addMapChip(MapChip(world_map_image, 51, MapChipProfiles::Types::Road, MapChipProfiles::Directions::Horizontal, true));


	return map_objects;
}
