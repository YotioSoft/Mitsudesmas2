#include "GameMap.h"

GameMap::GameMap() {}
GameMap::GameMap(Array<Array<Array<MapObject>>> init_objects_map,
	Array<Array<Array<MapChipProfiles::Directions>>> init_object_directions_map,
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

bool GameMap::isPassable(SquarePosition position) {
	bool pos_passable = true;
	for (int i=0; i<objects_map[position.y][position.x].size(); i++) {
		if (!objects_map[position.y][position.x][i].getChipP(object_directions_map[position.y][position.x][i])->isPassable()) {
			pos_passable = false;
		}
	}
	
	for (int i=0; i<couples.size(); i++) {
		if (couples[i].character1.position.x == position.x && couples[i].character1.position.y == position.y) {
			pos_passable = false;
		}
		if (couples[i].character2.position.x == position.x && couples[i].character2.position.y == position.y) {
			pos_passable = false;
		}
	}
	
	for (int i=0; i<soli.size(); i++) {
		if (soli[i].position.x == position.x && soli[i].position.y == position.y) {
			pos_passable = false;
		}
	}
	
	return pos_passable;
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
		if (center_square.x + 1 < objects_map[center_square.y].size() && isPassable(SquarePosition(center_square.x + 1, center_square.y))) {
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
		if (center_square.y + 1 < objects_map.size() && isPassable(SquarePosition(center_square.x, center_square.y + 1))) {
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
		for (int i=0; i<couples.size(); i++) {
			if (direction == Direction::TOP) {
				couples[i].character1.character.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
				couples[i].character2.character.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				couples[i].character1.character.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
				couples[i].character2.character.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				couples[i].character1.character.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
				couples[i].character2.character.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				couples[i].character1.character.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
				couples[i].character2.character.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
			}
		}
		
		for (int i=0; i<soli.size(); i++) {
			if (direction == Direction::TOP) {
				soli[i].character.move(Point(Direction::BOTTOM.x / slow, Direction::BOTTOM.y / slow));
			}
			else if (direction == Direction::RIGHT) {
				soli[i].character.move(Point(Direction::LEFT.x / slow, Direction::LEFT.y / slow));
			}
			else if (direction == Direction::BOTTOM) {
				soli[i].character.move(Point(Direction::TOP.x / slow, Direction::TOP.y / slow));
			}
			else if (direction == Direction::LEFT) {
				soli[i].character.move(Point(Direction::RIGHT.x / slow, Direction::RIGHT.y / slow));
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
	return Size(objects_map[0].size(), objects_map.size());
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
		if (y < 0 || y >= objects_map.size()) {
			continue;
		}

		for (int x = center_square.x - Scene::Width() / CHIP_SIZE.x / 2 - 2; x < center_square.x + Scene::Width() / CHIP_SIZE.x / 2 + 2; x++) {
			if (x < 0 || x >= objects_map[y].size()) {
				continue;
			}
			
			for (int i = 0; i < objects_map[y][x].size(); i++) {
				objects_map[y][x][i].draw(object_directions_map[y][x][i], squarePositionToPoint(SquarePosition(x, y)));
			}
		}
		
		// 他のキャラクターの描画
		for (int i=0; i<couples.size(); i++) {
			if (couples[i].character1.position.y == y) {
				if (couples[i].locked_on) {
					couples[i].character1.character.drawLight();
				}
				else {
					couples[i].character1.character.draw();
				}
			}
			if (couples[i].character2.position.y == y) {
				if (couples[i].locked_on) {
					couples[i].character2.character.drawLight();
				}
				else {
					couples[i].character2.character.draw();
				}
			}
		}
		for (int i=0; i<soli.size(); i++) {
			if (soli[i].position.y == y) {
				if (soli[i].locked_on) {
					soli[i].character.drawLight();
				}
				else {
					soli[i].character.draw();
				}
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
		
		if (x < objects_map[0].size() - 1) {
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
	if (y < objects_map.size() - 1) {
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
	if (x < objects_map[0].size() - 1) {
		for (int i = 0; i < objects_map[y][x + 1].size(); i++) {
			if (objects_map[y][x + 1][i].getType() == type) {
				right = true;
			}
		}
		
		if (y < objects_map.size() - 1) {
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
	JSONReader read_map(file_path);
	int y = 0;
	for (const auto& map_squares : read_map[U"objects"].arrayView()) {
		objects_map.push_back(Array<Array<MapObject>>());
		int x = 0;

		for (const auto& map_square : map_squares.arrayView()) {
			objects_map[y].push_back(Array<MapObject>());

			for (const auto& map_chip_name : map_square.arrayView()) {
				objects_map[y][x].push_back(objects[map_chip_name.getString()]);
			}
			x++;
		}
		y++;
	}

	y = 0;
	for (const auto& map_squares : read_map[U"objects"].arrayView()) {
		object_directions_map.push_back(Array<Array<MapChipProfiles::Directions>>());
		int x = 0;

		for (const auto& map_square : map_squares.arrayView()) {
			object_directions_map[y].push_back(Array<MapChipProfiles::Directions>());

			int i = 0;
			for (const auto& map_chip_name : map_square.arrayView()) {
				// 向きを推定
				switch (objects_map[y][x][i].getType()) {
					case MapChipProfiles::Types::Road:
						object_directions_map[y][x].push_back(setConnectableObjectDirection(SquarePosition(x, y), objects_map[y][x][i].getType(), 11));
						break;
					case MapChipProfiles::Types::Mountain:
						object_directions_map[y][x].push_back(setConnectableObjectDirection(SquarePosition(x, y), objects_map[y][x][i].getType(), 9));
						break;
					case MapChipProfiles::Types::ExpandableTree:
						object_directions_map[y][x].push_back(setUnconnectableObjectDirection(SquarePosition(x, y), objects_map[y][x][i]));
						break;
					default:
						object_directions_map[y][x].push_back(MapChipProfiles::None);
						break;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}

void GameMap::save(FilePath file_path) {
	JSONWriter map_data;
	map_data.startObject();
	{
		map_data.key(U"objects").startArray();
		{
			for (int y = 0; y < objects_map.size(); y++) {
				map_data.startArray();
				{
					for (int x = 0; x < objects_map[y].size(); x++) {
						map_data.startArray();
						{
							for (int i = 0; i < objects_map[y][x].size(); i++) {
								map_data.write(objects_map[y][x][i].getName());
							}
						}
						map_data.endArray();
					}
				}
				map_data.endArray();
			}
		}
		map_data.endArray();
	}
	map_data.endObject();
	map_data.save(file_path);
}

