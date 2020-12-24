#pragma once
#include "header.h"
#include "MapObject.h"
#include "Character.h"

class GameMap
{
private:
	// オブジェクト
	std::map<String, MapObject> objects;

	// オブジェクトのマップ
	Array<Array<Array<MapObject>>> objects_map;

	// マップ上のオブジェクトの向き
	Array<Array<Array<MapChipProfiles::Directions>>> object_directions_map;

	// プレイヤー
	Character player;

	// マップ上のキャラクタ
	Array<Character> characters;

	// 中心座標
	SquarePosition center_square;

	// 座標のオフセット（-32～32）
	Point square_position_offset = Point(0, 0);

public:
	// マップ登録
	GameMap(Array<Array<Array<MapObject>>> init_objects_map,
		Array<Array<Array<MapChipProfiles::Directions>>> init_object_directions_map,
		Character init_player,
		SquarePosition init_center_square);
	GameMap(FilePath map_file_path,
		std::map<String, MapObject> init_objects,
		Character init_player,
		SquarePosition init_center_square);

	// 視点を移動
	SquarePosition moveCamera(Point direction);

	// マップ描画
	void draw();

	// チップの座標から画面上の座標に変換
	Point squarePositionToPoint(SquarePosition square_position);

	// 画面上の座標からチップの座標に変換
	SquarePosition pointToSquarePosition(Point point);

	// 周囲の道を検出し指定されたマスの道の向きを決定
	MapChipProfiles::Directions setRoadDirection(SquarePosition square_position);

	// マップ読み込み
	void load(FilePath file_path);

	// マップ保存
	void save(FilePath file_path);
};

