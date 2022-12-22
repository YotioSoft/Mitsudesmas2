#include <GameMap.h>

GameMap::GameMap() {}
GameMap::GameMap(Grid<Array<MapObject>> init_objects_map,
	Grid<Array<MapChipProfiles::Directions>> init_object_directions_map,
	Character init_player,
	SquarePosition init_center_square) {
	objects_map = init_objects_map;
	object_directions_map = init_object_directions_map;
	player = init_player;
	center_square = init_center_square;
}

GameMap::GameMap(FilePath map_file_path,
	std::map<String, MapObject> init_objects,
	Character init_player,
	SquarePosition init_center_square) {
	player = init_player;
	objects = init_objects;
	center_square = init_center_square;

	// マップの読み込み
	load(map_file_path);
}

void GameMap::putCharacter(Citizen character) {
	character.character.setPosition(squarePositionToPoint(character.position));
	soli << character;
}
void GameMap::putCouple(Couple couple) {
	couple.character1.character.setPosition(squarePositionToPoint(couple.character1.position));
	couple.character2.character.setPosition(squarePositionToPoint(couple.character2.position));
	couples << couple;
}
void GameMap::putSpeaker(PlacedItem item) {
	item.item.setPosition(squarePositionToPoint(item.position));
	speakers << item;
}
void GameMap::putFood(PlacedItem item) {
	item.item.setPosition(squarePositionToPoint(item.position));
	foods << item;
}
void GameMap::putWatch(PlacedItem item) {
	item.item.setPosition(squarePositionToPoint(item.position));
	watches << item;
}
void GameMap::putBulldozer(PlacedItem item) {
	item.item.setPosition(squarePositionToPoint(item.position));
	bulldozers << item;
}

bool GameMap::isThereAnything(SquarePosition position) {
	if (!isPassable(position)) {
		return true;
	}
	SquarePosition player_position = center_square;
	center_square = position;
	if (isThereSpeaker()) {
		center_square = player_position;
		return true;
	}
	if (isThereFood()) {
		center_square = player_position;
		return true;
	}
	if (isThereWatch()) {
		center_square = player_position;
		return true;
	}
	if (isThereBulldozer()) {
		center_square = player_position;
		return true;
	}
	center_square = player_position;
	return false;
}

bool GameMap::isPassable(SquarePosition position) {
	if (!isThereCouple(position)) {
		return false;
	}

	bool pos_passable = true;
	for (int i=0; i<objects_map[position.y][position.x].size(); i++) {
		if (!objects_map[position.y][position.x][i].getChipP(object_directions_map[position.y][position.x][i])->isPassable()) {
			pos_passable = false;
		}
	}

	for (int i = 0; i < soli.size(); i++) {
		if (soli[i].position.x == position.x && soli[i].position.y == position.y) {
			pos_passable = false;
		}
	}
	
	return pos_passable;
}

bool GameMap::isThereCouple(SquarePosition position) {
	bool pos_passable = true;

	for (int i = 0; i < couples.size(); i++) {
		if (couples[i].character1.position.x == position.x && couples[i].character1.position.y == position.y) {
			pos_passable = false;
		}
		if (couples[i].character2.position.x == position.x && couples[i].character2.position.y == position.y) {
			pos_passable = false;
		}
	}

	return pos_passable;
}

bool GameMap::isThereSpeaker() {
	for (int i = 0; i < speakers.size(); i++) {
		if (speakers[i].position.x == center_square.x && speakers[i].position.y == center_square.y) {
			return true;
		}
	}
	return false;
}

void GameMap::removeCenterSpeaker() {
	for (int i = 0; i < speakers.size(); i++) {
		if (speakers[i].position.x == center_square.x && speakers[i].position.y == center_square.y) {
			speakers.remove_at(i);
			break;
		}
	}
}

bool GameMap::isThereFood() {
	for (int i = 0; i < foods.size(); i++) {
		if (foods[i].position.x == center_square.x && foods[i].position.y == center_square.y) {
			return true;
		}
	}
	return false;
}

void GameMap::removeCenterFood() {
	for (int i = 0; i < foods.size(); i++) {
		if (foods[i].position.x == center_square.x && foods[i].position.y == center_square.y) {
			foods.remove_at(i);
			break;
		}
	}
}

bool GameMap::isThereWatch() {
	for (int i = 0; i < watches.size(); i++) {
		if (watches[i].position.x == center_square.x && watches[i].position.y == center_square.y) {
			return true;
		}
	}
	return false;
}

void GameMap::removeCenterWatch() {
	for (int i = 0; i < watches.size(); i++) {
		if (watches[i].position.x == center_square.x && watches[i].position.y == center_square.y) {
			watches.remove_at(i);
			break;
		}
	}
}

bool GameMap::isThereBulldozer() {
	for (int i = 0; i < bulldozers.size(); i++) {
		if (bulldozers[i].position.x == center_square.x && bulldozers[i].position.y == center_square.y) {
			return true;
		}
	}
	return false;
}

void GameMap::removeCenterBulldozer() {
	for (int i = 0; i < bulldozers.size(); i++) {
		if (bulldozers[i].position.x == center_square.x && bulldozers[i].position.y == center_square.y) {
			bulldozers.remove_at(i);
			break;
		}
	}
}

Character* GameMap::getCharacter(SquarePosition position) {
	for (int i=0; i<couples.size(); i++) {
		if (couples[i].character1.position.x == position.x && couples[i].character1.position.y == position.y) {
			return &(couples[i].character1.character);
		}
		if (couples[i].character2.position.x == position.x && couples[i].character2.position.y == position.y) {
			return &(couples[i].character2.character);
		}
	}
	return nullptr;
}

Couple* GameMap::getCouple(SquarePosition position) {
	for (int i=0; i<couples.size(); i++) {
		if (couples[i].character1.position.x == position.x && couples[i].character1.position.y == position.y) {
			return &(couples[i]);
		}
		if (couples[i].character2.position.x == position.x && couples[i].character2.position.y == position.y) {
			return &(couples[i]);
		}
	}
	return nullptr;
}

SquarePosition GameMap::moveCamera(Point direction) {
	int slow = 1;
	if (slow_mode) {
		slow = 4;
	}
	
	// (move_x, move_y)分移動
	square_position_offset += Point(direction.x / slow, direction.y / slow);

	// プレイヤーを中心座標に動かす
	player.walk(direction);
	
	bool can_move = true;

	// オフセットが32を超えたら
	if (square_position_offset.x > CHIP_SIZE.x / 2) {
		// 中心座標を1マス右にずらしてもマップ外に出ない場合は1マス右にずらす
		if (center_square.x + 1 < objects_map.width() && isPassable(SquarePosition(center_square.x + 1, center_square.y))) {
			center_square.x++;
			square_position_offset.x -= CHIP_SIZE.x;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= Point(direction.x / slow, direction.y / slow);
			can_move = false;
		}
	}
	if (square_position_offset.y > CHIP_SIZE.y / 2) {
		// 中心座標を1マス下にずらしてもマップ外に出ない場合は1マス下にずらす
		if (center_square.y + 1 < objects_map.height() && isPassable(SquarePosition(center_square.x, center_square.y + 1))) {
			center_square.y++;
			square_position_offset.y -= CHIP_SIZE.y;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= Point(direction.x / slow, direction.y / slow);
			can_move = false;
		}
	}

	// オフセットが-32を未満になったら
	if (square_position_offset.x < - CHIP_SIZE.x / 2) {
		// 中心座標を1マス左にずらしてもマップ外に出ない場合は1マス左にずらす
		if (center_square.x - 1 >= 0 && isPassable(SquarePosition(center_square.x - 1, center_square.y))) {
			center_square.x--;
			square_position_offset.x += CHIP_SIZE.x;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= Point(direction.x / slow, direction.y / slow);
			can_move = false;
		}
	}
	if (square_position_offset.y < - CHIP_SIZE.y / 2) {
		// 中心座標を1マス上にずらしてもマップ外に出ない場合は1マス上にずらす
		if (center_square.y - 1 >= 0 && isPassable(SquarePosition(center_square.x, center_square.y - 1))) {
			center_square.y--;
			square_position_offset.y += CHIP_SIZE.y;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= Point(direction.x / slow, direction.y / slow);
			can_move = false;
		}
	}
	
	// カメラが移動した場合、他のキャラクターを動かす
	if (can_move) {
		for (auto& couple : couples) {
			if (direction == Direction::TOP) {
				couple.character1.character.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
				couple.character2.character.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				couple.character1.character.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
				couple.character2.character.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				couple.character1.character.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
				couple.character2.character.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				couple.character1.character.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
				couple.character2.character.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}
		
		for (auto& one_soli : soli) {
			if (direction == Direction::TOP) {
				one_soli.character.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				one_soli.character.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				one_soli.character.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				one_soli.character.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}

		for (auto& speaker : speakers) {
			if (direction == Direction::TOP) {
				speaker.item.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				speaker.item.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				speaker.item.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				speaker.item.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}

		for (auto& food : foods) {
			if (direction == Direction::TOP) {
				food.item.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				food.item.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				food.item.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				food.item.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}

		for (auto& watch : watches) {
			if (direction == Direction::TOP) {
				watch.item.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				watch.item.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				watch.item.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				watch.item.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}

		for (auto& bulldozer : bulldozers) {
			if (direction == Direction::TOP) {
				bulldozer.item.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				bulldozer.item.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				bulldozer.item.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				bulldozer.item.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}
	}
	
	// プレイヤーの周囲にキャラクターがいたらロックオン
	bool locked_on_already = false;
	for (int i=0; i<couples.size(); i++) {
		couples[i].locked_on = false;
		
		if (player.getDirection() == Direction::TOP) {
			if (couples[i].character1.position.x <= center_square.x && couples[i].character2.position.x >= center_square.x &&
				couples[i].character1.position.y - center_square.y >= -2 && couples[i].character1.position.y - center_square.y <= -1 &&
				!locked_on_already) {
				couples[i].locked_on = true;
				locked_on_already = true;
			}
		}
		else if (player.getDirection() == Direction::LEFT) {
			if (couples[i].character1.position.y == center_square.y &&
				((couples[i].character1.position.x - center_square.x >= -2 && couples[i].character1.position.x - center_square.x <= -1) ||
				 (couples[i].character2.position.x - center_square.x >= -2 && couples[i].character2.position.x - center_square.x <= -1)) &&
				!locked_on_already) {
				couples[i].locked_on = true;
				locked_on_already = true;
			}
		}
		else if (player.getDirection() == Direction::BOTTOM) {
			if (couples[i].character1.position.x <= center_square.x && couples[i].character2.position.x >= center_square.x &&
				couples[i].character1.position.y - center_square.y <= 2 && couples[i].character1.position.y - center_square.y >= 1 &&
				!locked_on_already) {
				couples[i].locked_on = true;
				locked_on_already = true;
			}
		}
		else if (player.getDirection() == Direction::RIGHT) {
			if (couples[i].character1.position.y == center_square.y &&
				((couples[i].character1.position.x - center_square.x <= 2 && couples[i].character1.position.x - center_square.x >= 1) ||
				 (couples[i].character2.position.x - center_square.x <= 2 && couples[i].character2.position.x - center_square.x >= 1)) &&
				!locked_on_already) {
				couples[i].locked_on = true;
				locked_on_already = true;
			}
		}
	}
	for (int i=0; i<soli.size(); i++) {
		soli[i].locked_on = false;
		
		if (player.getDirection() == Direction::TOP) {
			if (soli[i].position.x <= center_square.x &&
				soli[i].position.y - center_square.y >= -2 && soli[i].position.y - center_square.y <= -1 &&
				!locked_on_already) {
				soli[i].locked_on = true;
				locked_on_already = true;
			}
		}
		else if (player.getDirection() == Direction::LEFT) {
			if (soli[i].position.y == center_square.y &&
				(soli[i].position.x - center_square.x >= -2 && soli[i].position.x - center_square.x <= -1) &&
				!locked_on_already) {
				soli[i].locked_on = true;
				locked_on_already = true;
			}
		}
		else if (player.getDirection() == Direction::BOTTOM) {
			if (soli[i].position.x <= center_square.x && soli[i].position.x >= center_square.x &&
				soli[i].position.y - center_square.y <= 2 && soli[i].position.y - center_square.y >= 1 &&
				!locked_on_already) {
				soli[i].locked_on = true;
				locked_on_already = true;
			}
		}
		else if (player.getDirection() == Direction::RIGHT) {
			if (soli[i].position.y == center_square.y &&
				(soli[i].position.x - center_square.x <= 2 && soli[i].position.x - center_square.x >= 1) &&
				!locked_on_already) {
				soli[i].locked_on = true;
				locked_on_already = true;
			}
		}
	}

	return center_square;
}

void GameMap::setSlowMode(bool enable) {
	slow_mode = enable;
}

int GameMap::space() {
	for (int i=0; i<couples.size(); i++) {
		if (couples[i].locked_on) {
			if (couples[i].crowded) {
				couples[i].character1.moving = Point(-4, 0);
				couples[i].character2.moving = Point(4, 0);
				couples[i].crowded = false;
				
				return Result::SUCCESS;
			}
			else {
				return Result::FAILURE;
			}
		}
	}
	for (int i=0; i<soli.size(); i++) {
		if (soli[i].locked_on) {
			return Result::FAILURE;
		}
	}
	return Result::NONE;
}

Size GameMap::getMapSize() {
	return objects_map.size();
}

void GameMap::draw() {
	// 移動中のキャラクターの処理
	for (int i=0; i<couples.size(); i++) {
		if (couples[i].character1.moving != Point(0, 0)) {
			SquarePosition beforePosition = couples[i].character1.position;
			
			Point c1_pos = couples[i].character1.character.getPosition();
			couples[i].character1.character.setPosition(Point(c1_pos.x + couples[i].character1.moving.x, c1_pos.y));
			Point c2_pos = couples[i].character2.character.getPosition();
			couples[i].character2.character.setPosition(Point(c2_pos.x + couples[i].character2.moving.x, c2_pos.y));
			
			if (squarePositionToPoint(beforePosition).x - couples[i].character1.character.getPosition().x >= CHIP_SIZE.x) {
				couples[i].character1.moving = Point(0, 0);
				couples[i].character1.position.x -= 1;
				couples[i].character2.moving = Point(0, 0);
				couples[i].character2.position.x += 1;
			}
		}
	}
	
	// マップの描画（見えるところだけ）
	for (int y = center_square.y - Scene::Height() / CHIP_SIZE.y / 2 - 2; y < center_square.y + Scene::Height() / CHIP_SIZE.y / 2 + 2; y++) {
		if (y < 0 || y >= objects_map.height()) {
			continue;
		}

		for (int x = center_square.x - Scene::Width() / CHIP_SIZE.x / 2 - 2; x < center_square.x + Scene::Width() / CHIP_SIZE.x / 2 + 2; x++) {
			if (x < 0 || x >= objects_map.width()) {
				continue;
			}
			
			for (int i = 0; i < objects_map[y][x].size(); i++) {
				objects_map[y][x][i].draw(object_directions_map[y][x][i], squarePositionToPoint(SquarePosition(x, y)));
			}
		}
		
		// 他のキャラクターの描画
		for (auto &couple : couples) {
			if (couple.character1.position.y == y) {
				if (couple.locked_on) {
					couple.character1.character.drawLight();
				}
				else {
					couple.character1.character.draw();
				}
			}
			if (couple.character2.position.y == y) {
				if (couple.locked_on) {
					couple.character2.character.drawLight();
				}
				else {
					couple.character2.character.draw();
				}
			}
		}
		for (auto &one_soli : soli) {
			if (one_soli.position.y == y) {
				if (one_soli.locked_on) {
					one_soli.character.drawLight();
				}
				else {
					one_soli.character.draw();
				}
			}
		}

		// アイテムの描画
		for (auto &speaker : speakers) {
			if (speaker.position.y == y) {
				speaker.item.draw();
			}
		}
		for (auto &food : foods) {
			if (food.position.y == y) {
				food.item.draw();
			}
		}
		for (auto &watch : watches) {
			if (watch.position.y == y) {
				watch.item.draw();
			}
		}
		for (auto& bulldozer : bulldozers) {
			if (bulldozer.position.y == y) {
				bulldozer.item.draw();
			}
		}
		
		// プレイヤーの描画
		if (center_square.y == y) {
			player.draw();
		}
	}
}

Point GameMap::squarePositionToPoint(SquarePosition square_position) {
	int dy = square_position.y - center_square.y;
	int dx = square_position.x - center_square.x;

	return Point(Scene::Width() / 2 - square_position_offset.x - CHIP_SIZE.x / 2 + dx * CHIP_SIZE.x,
		Scene::Height() / 2 - square_position_offset.y - CHIP_SIZE.y / 2 + dy * CHIP_SIZE.y);
}

MapChipProfiles::Directions GameMap::setConnectableObjectDirection(SquarePosition square_position, MapChipProfiles::Types type, int max_size) {
	bool top = false;
	bool right = false;
	bool bottom = false;
	bool left = false;
	
	bool top_right = false;
	bool right_bottom = false;
	bool bottom_left = false;
	bool top_left = false;

	int x = square_position.x;
	int y = square_position.y;

	if (y > 0) {
		for (int i = 0; i < objects_map[y - 1][x].size(); i++) {
			if (objects_map[y - 1][x][i].getType() == type) {
				top = true;
			}
		}
		
		if (x < objects_map.width() - 1) {
			for (int i = 0; i < objects_map[y - 1][x + 1].size(); i++) {
				if (objects_map[y - 1][x + 1][i].getType() == type) {
					top_right = true;
				}
			}
		}
	}
	if (x > 0) {
		for (int i = 0; i < objects_map[y][x - 1].size(); i++) {
			if (objects_map[y][x - 1][i].getType() == type) {
				left = true;
			}
		}
		
		if (y > 0) {
			for (int i = 0; i < objects_map[y - 1][x - 1].size(); i++) {
				if (objects_map[y - 1][x - 1][i].getType() == type) {
					top_left = true;
				}
			}
		}
	}
	if (y < objects_map.height() - 1) {
		for (int i = 0; i < objects_map[y + 1][x].size(); i++) {
			if (objects_map[y + 1][x][i].getType() == type) {
				bottom = true;
			}
		}
		
		if (x > 0) {
			for (int i = 0; i < objects_map[y + 1][x - 1].size(); i++) {
				if (objects_map[y + 1][x - 1][i].getType() == type) {
					bottom_left = true;
				}
			}
		}
	}
	if (x < objects_map.width() - 1) {
		for (int i = 0; i < objects_map[y][x + 1].size(); i++) {
			if (objects_map[y][x + 1][i].getType() == type) {
				right = true;
			}
		}
		
		if (y < objects_map.height() - 1) {
			for (int i = 0; i < objects_map[y + 1][x + 1].size(); i++) {
				if (objects_map[y + 1][x + 1][i].getType() == type) {
					right_bottom = true;
				}
			}
		}
	}

	MapChipProfiles::Directions ret_direction = MapChipProfiles::Directions::None;
	if (max_size >= 9) {
		if (top && right && bottom && left) {
			if (max_size == 9) {
				if (right_bottom && bottom_left && top_right && top_left) {
					return MapChipProfiles::Directions::TopRightBottomLeft;
				}
				else {
					if (!right_bottom) {
						return MapChipProfiles::Directions::CircleTopLeft;
					}
					if (!bottom_left) {
						return MapChipProfiles::Directions::CircleTopRight;
					}
					if (!top_right) {
						return MapChipProfiles::Directions::CircleBottomLeft;
					}
					if (!top_left) {
						return MapChipProfiles::Directions::CircleRightBottom;
					}
				}
			} else {
				return MapChipProfiles::Directions::TopRightBottomLeft;;
			}
		}
		
		if (!top && right && bottom && left) {
			if (max_size == 9) {
				if (right_bottom && bottom_left) {
					return MapChipProfiles::Directions::RightBottomLeft;
				}
			} else {
				return MapChipProfiles::Directions::RightBottomLeft;
			}
		}
		if (top && right && bottom && !left) {
			if (max_size == 9) {
				if (top_right && right_bottom) {
					return MapChipProfiles::Directions::TopRightBottom;
				}
			} else {
				return MapChipProfiles::Directions::TopRightBottom;
			}
		}
		if (top && !right && bottom && left) {
			if (max_size == 9) {
				if (bottom_left && top_left) {
					return MapChipProfiles::Directions::TopBottomLeft;
				}
			} else {
				return MapChipProfiles::Directions::TopBottomLeft;
			}
		}
		if (top && right && !bottom && left) {
			if (max_size == 9) {
				if (top_left && top_right) {
					return MapChipProfiles::Directions::TopRightLeft;
				}
			} else {
				return MapChipProfiles::Directions::TopRightLeft;
			}
		}
	}
	
	if (top && !right && !bottom && left) {
		return MapChipProfiles::Directions::TopLeft;
	}
	if (!top && !right && bottom && left) {
		return MapChipProfiles::Directions::BottomLeft;
	}
	if (top && right && !bottom && !left) {
		return MapChipProfiles::Directions::TopRight;
	}
	if (!top && right && bottom && !left) {
		return MapChipProfiles::Directions::RightBottom;
	}
	
	if (max_size >= 11) {
		if (top || bottom) {
			return MapChipProfiles::Directions::Vertical;
		}
		if (right || left) {
			return MapChipProfiles::Directions::Horizontal;
		}
	}
	
	return ret_direction;
}

MapChipProfiles::Directions GameMap::setUnconnectableObjectDirection(SquarePosition square_position, MapObject object) {
	int x = square_position.x;
	int y = square_position.y;
	
	// 同じオブジェクトの群の中で最も上のものとの距離を求める
	int temp_y = y;
	bool same_object_exists_y;
	do {
		same_object_exists_y = false;
		for (int i=0; i<objects_map[temp_y-1][x].size(); i++) {
			if (objects_map[temp_y-1][x][i].getName() == object.getName()) {
				same_object_exists_y = true;
				break;
			}
		}
		if (same_object_exists_y) {
			temp_y -= 1;
			
			if (temp_y - 1 < 0) {
				temp_y = 0;
				same_object_exists_y = false;
			}
		}
	} while (same_object_exists_y);
	int distance_topmost_y = y - temp_y;
	
	// 同じオブジェクトの群の中で最も左のものとの距離を求める
	int temp_x = x;
	bool same_object_exists_x;
	do {
		same_object_exists_x = false;
		for (int i=0; i<objects_map[y][temp_x-1].size(); i++) {
			if (objects_map[y][temp_x-1][i].getName() == object.getName()) {
				same_object_exists_x = true;
				break;
			}
		}
		if (same_object_exists_x) {
			temp_x -= 1;
			
			if (temp_x - 1 < 0) {
				temp_x = 0;
				same_object_exists_x = false;
			}
		}
	} while (same_object_exists_x);
	int distance_leftmost_x = x - temp_x;
	
	// 基準となる座標を算出
	int start_y = distance_topmost_y % object.getObjectSize().y;
	int start_x = distance_leftmost_x % object.getObjectSize().x;
	
	if (start_x == 0 && start_y == 0) {
		return MapChipProfiles::Directions::RightBottom;
	}
	if (start_x == 1 && start_y == 0) {
		return MapChipProfiles::Directions::BottomLeft;
	}
	if (start_x == 1 && start_y == 1) {
		return MapChipProfiles::Directions::TopLeft;
	}
	if (start_x == 0 && start_y == 1) {
		return MapChipProfiles::Directions::TopRight;
	}
	
	return MapChipProfiles::Directions::None;
}

void GameMap::load(FilePath file_path) {
	const CSV csv(file_path);

	if (not csv) {
		throw Error{ U"Failed to load map data" };
	}

	objects_map.resize(csv.columns(0), csv.rows()/2);
	object_directions_map.resize(csv.columns(0), csv.rows()/2);

	int x, y;
	for (size_t row = 0; row < csv.rows(); row++) {
		y = row / 2;

		for (size_t column = 0; column < csv[row].size(); column++) {
			x = column;
			
            if (csv[row][column].length() > 0)
                objects_map[y][x].push_back(objects[csv[row][column]]);
		}
	}

	for (auto y : step(objects_map.height())) {
		for (auto x : step(objects_map.width())) {
			for (auto map_obj : objects_map[y][x]) {
				// 向きを推定
				switch (map_obj.getType()) {
					case MapChipProfiles::Types::Road:
						object_directions_map[y][x].push_back(setConnectableObjectDirection(SquarePosition(x, y), map_obj.getType(), 11));
						break;
					case MapChipProfiles::Types::Mountain:
						object_directions_map[y][x].push_back(setConnectableObjectDirection(SquarePosition(x, y), map_obj.getType(), 9));
						break;
					case MapChipProfiles::Types::ExpandableTree:
						object_directions_map[y][x].push_back(setUnconnectableObjectDirection(SquarePosition(x, y), map_obj));
						break;
					default:
						object_directions_map[y][x].push_back(MapChipProfiles::None);
						break;
				}
			}
			x++;
		}
		y++;
	}
}
