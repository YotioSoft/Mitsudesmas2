#include "Character.h"

Character::Character() {}

Character::Character(Image new_image, const Point init_direction, bool init_always_center) {
	texture = Texture(ImageTools::zoomImage2x(new_image));
	direction = init_direction;
	alwaysCenter = init_always_center;
	
	if (direction == Direction::TOP) {
		index = character_profiles::forward_2;
	}
	else if (direction == Direction::LEFT) {
		index = character_profiles::left_2;
	}
	else if (direction == Direction::BOTTOM) {
		index = character_profiles::backward_2;
	}
	else if (direction == Direction::RIGHT) {
		index = character_profiles::right_2;
	}

	if (alwaysCenter) {
		position = Scene::Center() - Point(CHIP_SIZE.x / 2, CHIP_SIZE.y);
	}
}

void Character::draw() {
	texture(character_profiles::pos_on_image[index]).draw(position);
}

void Character::setPosition(Point set_position) {
	position = set_position;
}

void Character::walk(Point move_direction) {
	if (move_direction == direction) {
		oneStep();
	}
	else {
		direction = move_direction;

		if (move_direction == Direction::TOP) {
			index = character_profiles::forward_2;
		}
		else if (move_direction == Direction::LEFT) {
			index = character_profiles::left_2;
		}
		else if (move_direction == Direction::BOTTOM) {
			index = character_profiles::backward_2;
		}
		else if (move_direction == Direction::RIGHT) {
			index = character_profiles::right_2;
		}
	}

	if (!alwaysCenter) {
		position += move_direction;
	}
}

void Character::oneStep() {
	if (index % 3 == 2) {
		index -= 2;
	}
	else {
		index++;
	}
}
