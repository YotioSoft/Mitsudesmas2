#include <Item.h>

Item::Item() {}

Item::Item(Image new_image) {
	texture = Texture(ImageTools::zoomImage2x(new_image));
}

void Item::draw() {
	texture.draw(position);
}

void Item::drawLight() {
	const ScopedColorAdd2D state(Color(80, 80, 80, 0));
	texture.draw(position);
}

void Item::setPosition(Point set_position) {
	position = set_position;
}

Point Item::getPosition() {
	return position;
}
