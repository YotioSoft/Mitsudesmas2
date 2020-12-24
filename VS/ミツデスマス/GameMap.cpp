#include "GameMap.h"

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

SquarePosition GameMap::moveCamera(Point direction) {
	// (move_x, move_y)分移動
	square_position_offset += Point(direction.x, direction.y);

	// プレイヤーを中心座標に動かす
	player.walk(direction);

	// オフセットが32を超えたら
	if (square_position_offset.x > CHIP_SIZE.x / 2) {
		// 中心座標を1マス右にずらしてもマップ外に出ない場合は1マス右にずらす
		if (center_square.x + 1 < objects_map[center_square.y].size()) {
			center_square.x++;
			square_position_offset.x -= CHIP_SIZE.x;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= direction;
		}
	}
	if (square_position_offset.y > CHIP_SIZE.y / 2) {
		// 中心座標を1マス右にずらしてもマップ外に出ない場合は1マス右にずらす
		if (center_square.y + 1 < objects_map.size()) {
			center_square.y++;
			square_position_offset.y -= CHIP_SIZE.y;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= direction;
		}
	}

	// オフセットが-32を未満になったら
	if (square_position_offset.x < - CHIP_SIZE.x / 2) {
		// 中心座標を1マス左にずらしてもマップ外に出ない場合は1マス左にずらす
		if (center_square.x - 1 >= 0) {
			center_square.x--;
			square_position_offset.x += CHIP_SIZE.x;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= direction;
		}
	}
	if (square_position_offset.y < - CHIP_SIZE.y / 2) {
		// 中心座標を1マス左にずらしてもマップ外に出ない場合は1マス左にずらす
		if (center_square.y - 1 >= 0) {
			center_square.y--;
			square_position_offset.y += CHIP_SIZE.y;
		}
		// マップ外に出る場合はカメラの移動を無効とする
		else {
			square_position_offset -= direction;
		}
	}

	return center_square;
}

void GameMap::draw() {
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
	}

	player.draw();
}

Point GameMap::squarePositionToPoint(SquarePosition square_position) {
	int dy = square_position.y - center_square.y;
	int dx = square_position.x - center_square.x;

	return Point(Scene::Width() / 2 - square_position_offset.x - CHIP_SIZE.x / 2 + dx * CHIP_SIZE.x,
		Scene::Height() / 2 - square_position_offset.y - CHIP_SIZE.y / 2 + dy * CHIP_SIZE.y);
}

SquarePosition GameMap::pointToSquarePosition(Point point) {
	return SquarePosition(0, 0);
}

MapChipProfiles::Directions GameMap::setRoadDirection(SquarePosition square_position) {
	bool top = false;
	bool right = false;
	bool bottom = false;
	bool left = false;

	int x = square_position.x;
	int y = square_position.y;

	if (y > 0) {
		for (int i = 0; i < objects_map[y - 1][x].size(); i++) {
			if (objects_map[y - 1][x][i].getType() == MapChipProfiles::Road) {
				top = true;
			}
		}
	}
	if (x > 0) {
		for (int i = 0; i < objects_map[y][x - 1].size(); i++) {
			if (objects_map[y][x - 1][i].getType() == MapChipProfiles::Road) {
				left = true;
			}
		}
	}
	if (y < objects_map.size() - 1) {
		for (int i = 0; i < objects_map[y + 1][x].size(); i++) {
			if (objects_map[y + 1][x][i].getType() == MapChipProfiles::Road) {
				bottom = true;
			}
		}
	}
	if (x < objects_map.size() - 1) {
		for (int i = 0; i < objects_map[y][x + 1].size(); i++) {
			if (objects_map[y][x + 1][i].getType() == MapChipProfiles::Road) {
				right = true;
			}
		}
	}

	MapChipProfiles::Directions ret_direction;
	if (top || bottom) {
		ret_direction = MapChipProfiles::Directions::Vertical;
	}
	if (right || left) {
		ret_direction = MapChipProfiles::Directions::Horizontal;
	}
	if (!top && right && bottom && !left) {
		ret_direction = MapChipProfiles::Directions::RightBottom;
	}
	if (!top && right && bottom && left) {
		ret_direction = MapChipProfiles::Directions::RightBottomLeft;
	}
	if (!top && !right && bottom && left) {
		ret_direction = MapChipProfiles::Directions::BottomLeft;
	}
	if (top && right && bottom && !left) {
		ret_direction = MapChipProfiles::Directions::TopRightBottom;
	}
	if (top && right && bottom && left) {
		ret_direction = MapChipProfiles::Directions::TopRightBottomLeft;
	}
	if (top && !right && bottom && left) {
		ret_direction = MapChipProfiles::Directions::TopBottomLeft;
	}
	if (top && right && !bottom && !left) {
		ret_direction = MapChipProfiles::Directions::TopRight;
	}
	if (top && right && !bottom && left) {
		ret_direction = MapChipProfiles::Directions::TopRightLeft;
	}
	if (top && !right && !bottom && left) {
		ret_direction = MapChipProfiles::Directions::TopLeft;
	}
	return ret_direction;
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
				if (objects_map[y][x][i].getType() != MapChipProfiles::Types::Road) {
					object_directions_map[y][x].push_back(MapChipProfiles::None);
				}
				else {
					object_directions_map[y][x].push_back(setRoadDirection(SquarePosition(x, y)));
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

		map_data.key(U"directions").startArray();
		{
			for (int y = 0; y < object_directions_map.size(); y++) {
				map_data.startArray();
				{
					for (int x = 0; x < object_directions_map[y].size(); x++) {
						map_data.startArray();
						{
							for (int i = 0; i < object_directions_map[y][x].size(); i++) {
								map_data.write((int)object_directions_map[y][x][i]);
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
