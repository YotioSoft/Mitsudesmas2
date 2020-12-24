#pragma once
#include "header.h"
#include "MapChip.h"

class MapObject
{
private:
	// マップチップ
	Array<MapChip> chips;

	// 名前
	String name;

	// 種類
	MapChipProfiles::Types type;

public:
	// コンストラクタ
	MapObject();
	MapObject(String init_name, MapChipProfiles::Types init_type);
	MapObject(String init_name, MapChipProfiles::Types init_type, MapChip &init_chip);
	MapObject(String init_name, MapChipProfiles::Types init_type, Array<MapChip> &init_chips);

	// MapChipを追加
	void addMapChip(MapChip init_chip);

	// 名前の取得
	String getName();

	// すべての向きの取得
	Array<MapChipProfiles::Directions> getDirections();

	// チップのタイプ
	MapChipProfiles::Types getType();

	// 描画（実際の描画はchips.drawで行う）
	bool draw(const MapChipProfiles::Directions direction, const Point position);
};

