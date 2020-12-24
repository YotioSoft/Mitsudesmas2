#pragma once
#include "header.h"
#include "ImageTools.h"
#include "CharacterProfiles.h"

class Character
{
private:
	// 画像上のインデックス（0～11）
	int index;

	// キャラクターの向き
	Point direction;

	// 画像
	Texture texture;

	// キャラクターの座標
	Point position = Point(10, 10);

	// 常に中央にキャラクターを置くか？
	bool alwaysCenter = false;


public:
	// コンストラクタ
	Character();
	Character(Image new_image, const Point init_direction, bool init_always_center);

	// 描画
	void draw();

	// キャラクターの位置
	void setPosition(Point set_position);

	// キャラクターの徒歩
	void walk(Point move_direction);

	// 一歩分アニメーションを動かす
	void oneStep();
};

