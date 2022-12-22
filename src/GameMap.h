#pragma once
#include <header.h>
#include <MapObject.h>
#include <Character.h>
#include <Item.h>

typedef struct Citizen {
	Character character;
	SquarePosition position;
	Point moving = Point(0, 0);
	bool locked_on = false;
} Citizen;

typedef struct Couple {
	Citizen character1;
	Citizen character2;
	bool crowded = true;
	bool locked_on = false;
} Couple;

typedef struct PlacedItem {
	Item item;
	SquarePosition position;
} PlacedItem;

class GameMap
{
private:
	// オブジェクト
	std::map<String, MapObject> objects;

	// オブジェクトのマップ
	Grid<Array<MapObject>> objects_map;

	// マップ上のオブジェクトの向き
	Grid<Array<MapChipProfiles::Directions>> object_directions_map;

	// プレイヤー
	Character player;

	// マップ上のキャラクタ
	Array<Citizen> soli;
	Array<Couple> couples;
	Array<PlacedItem> speakers;
	Array<PlacedItem> foods;
	Array<PlacedItem> watches;
	Array<PlacedItem> bulldozers;

	// 中心座標
	SquarePosition center_square;

	// 座標のオフセット（-32?32）
	Point square_position_offset = Point(0, 0);

	// ロックオンされたマップチップの座標
	SquarePosition locked_on_map_chip;
	
	// 移動が遅いモード
	bool slow_mode = false;

public:
	// マップ登録
	GameMap();
	GameMap(Grid<Array<MapObject>> init_objects_map,
        Grid<Array<MapChipProfiles::Directions>> init_object_directions_map,
		Character init_player,
		SquarePosition init_center_square);
	GameMap(FilePath map_file_path,
		std::map<String, MapObject> init_objects,
		Character init_player,
		SquarePosition init_center_square);
	
	// キャラクターの設置
	void putCharacter(Citizen character);
	void putCouple(Couple couple);
	void putSpeaker(PlacedItem item);
	void putFood(PlacedItem item);
	void putWatch(PlacedItem item);
	void putBulldozer(PlacedItem item);
	
	// 通行可能か否か
	bool isThereAnything(SquarePosition position);
	bool isPassable(SquarePosition position);
	bool isThereCouple(SquarePosition position);

	// 拡声器の操作
	bool isThereSpeaker();
	void removeCenterSpeaker();

	// 食べ物の操作
	bool isThereFood();
	void removeCenterFood();

	// 時計の操作
	bool isThereWatch();
	void removeCenterWatch();

	// ブルドーザーの操作
	bool isThereObstacle();
	bool isThereBulldozer();
	void removeCenterBulldozer();
	
	// 座標上にいるキャラクターを取得
	Character* getCharacter(SquarePosition position);
	Couple* getCouple(SquarePosition position);

	// 視点を移動
	SquarePosition moveCamera(Point direction);
	
	// 移動の速さの設定
	void setSlowMode(bool enable);
	
	// キャラクターの間を空ける
	int space();

	// ブルドーザーでマップ上のオブジェクトを除去する
	void bulldoze();
	
	// マップサイズを取得
	Size getMapSize();

	// マップ描画
	void draw();

	// チップの座標から画面上の座標に変換
	Point squarePositionToPoint(SquarePosition square_position);

	// 画面上の座標からチップの座標に変換
	SquarePosition pointToSquarePosition(Point point);

	// 周囲の道を検出し指定されたマスの道の向きを決定
	MapChipProfiles::Directions setConnectableObjectDirection(SquarePosition square_position, MapChipProfiles::Types type, int max_size);
	MapChipProfiles::Directions setUnconnectableObjectDirection(SquarePosition square_position, MapObject object);

	// マップ読み込み
	void load(FilePath file_path);
};
