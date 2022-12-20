#include <Item.h>

Item::Item() {}

Item::Item(Image new_image) {
	texture = Texture(new_image);
}

void Item::draw() {
	texture.resized(48, 48).drawAt(position.x + 32, position.y + 32);
}

void Item::drawLight() {
	const ScopedColorAdd2D state(Color(80, 80, 80, 0));
	texture.resized(48, 48).drawAt(position.x + 32, position.y + 32);
}

void Item::setPosition(Point set_position) {
	position = set_position;
}

Point Item::getPosition() {
	return position;
}

void Item::move(Point move_direction) {
	position += move_direction;
}
