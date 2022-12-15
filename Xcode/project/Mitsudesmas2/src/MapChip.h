#pragma once
#include "header.h"
#include "ImageTools.h"
#include "MapChipProfiles.h"

class MapChip
{
private:
	// テクスチャ
	Texture texture;

	// チップの種類
	MapChipProfiles::Types type;

	// チップの向きの存在
	bool directiond_exist;

	// チップの向き
	MapChipProfiles::Directions direction;

	// キャラクターの通行の可否
	bool passable;

public:
	// コンストラクタ
	MapChip(Image &chip_image, int init_position_number, MapChipProfiles::Types init_type, MapChipProfiles::Directions init_direction, bool init_passable);

	// 方向
	MapChipProfiles::Directions getDirection();

	// 通行の可否
	bool isPassable();

	// 種類
	MapChipProfiles::Types getType();

	// 描画
	void draw(Point position);
	void draw(SquarePosition sposition);
};
