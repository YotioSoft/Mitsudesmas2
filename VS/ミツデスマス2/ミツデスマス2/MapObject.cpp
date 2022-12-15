#include "MapObject.h"

MapObject::MapObject(){}
MapObject::MapObject(String init_name, MapChipProfiles::Types init_type) {
	name = init_name;
	type = init_type;
}
MapObject::MapObject(String init_name, MapChipProfiles::Types init_type, MapChip &init_chip) {
	name = init_name;
	type = init_type;
	chips << init_chip;
}
MapObject::MapObject(String init_name, MapChipProfiles::Types init_type, Array<MapChip> &init_chips) {
	name = init_name;
	type = init_type;
	chips = init_chips;
}

void MapObject::addMapChip(MapChip init_chip) {
	chips << init_chip;
}

void MapObject::setObjectSize(Size new_size) {
	size = new_size;
}

Size MapObject::getObjectSize() {
	return size;
}

String MapObject::getName() {
	return name;
}

Array<MapChipProfiles::Directions> MapObject::getDirections() {
	Array<MapChipProfiles::Directions> ret_array;
	for (int i = 0; i < chips.size(); i++) {
		ret_array << chips[i].getDirection();
	}

	return ret_array;
}

MapChipProfiles::Types MapObject::getType() {
	return type;
}

MapChip* MapObject::getChipP(MapChipProfiles::Directions direction) {
	for (int i = 0; i < chips.size(); i++) {
		if (chips[i].getDirection() == direction) {
			return &chips[i];
		}
	}
	return nullptr;
}

bool MapObject::draw(const MapChipProfiles::Directions direction, const Point position) {
	for (int i = 0; i < chips.size(); i++) {
		if (chips[i].getDirection() == direction) {
			chips[i].draw(position);
			return true;
		}
	}
	return false;
}
