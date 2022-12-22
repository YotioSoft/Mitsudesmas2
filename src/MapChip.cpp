#include <MapChip.h>

MapChip::MapChip(Image &chip_image, int init_position_number, MapChipProfiles::Types init_type, MapChipProfiles::Directions init_direction, bool init_passable) {
	Image temp_image = Image(CHIP_SIZE);
	Point position_on_image = ImageTools::getObjectPositionOnImage(init_position_number, CHIP_SIZE, CHIPS_IN_A_ROW);
	for (int y = position_on_image.y; y < position_on_image.y + CHIP_SIZE.y; y++) {
		for (int x = position_on_image.x; x < position_on_image.x + CHIP_SIZE.x; x++) {
			temp_image[y - position_on_image.y][x - position_on_image.x] = chip_image[y][x];
		}
	}
	texture = Texture(temp_image);

	type = init_type;
	direction = init_direction;
	passable = init_passable;
}

MapChipProfiles::Directions MapChip::getDirection() {
	return direction;
}

bool MapChip::isPassable() {
	return passable;
}

MapChipProfiles::Types MapChip::getType() {
	return type;
}

void MapChip::draw(Point position) {
	texture.draw(position);
}
void MapChip::drawLight(Point position) {
	const ScopedColorAdd2D state(Color(80, 80, 80, 0));
	texture.draw(position);
}
