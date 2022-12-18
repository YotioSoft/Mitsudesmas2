#pragma once
#include <header.h>
#include <ImageTools.h>
#include <CharacterProfiles.h>

class Character
{
private:
	// 画像上のインデックス（0?11）
	int index;

	// キャラクターの向き
	Point direction;

	// 画像
	Texture texture;

	// キャラクターの座標
	Point position = Point(10, 10);

	// 常に中心座標か？
	bool alwaysCenter;

public:
	// コンストラクタ
	Character();
	Character(Image new_image, const Point init_direction, const bool init_always_center);

	// 描画
	void draw();
	void drawLight();

	// キャラクターの位置を設定
	void setPosition(Point set_position);
	
	// キャラクターの位置を取得
	Point getPosition();
	
	// キャラクターの向き
	Point getDirection();

	// キャラクターの徒歩
	void walk(Point move_direction);

	// 一歩分アニメーションを動かす
	void oneStep();
	
	// キャラクターの移動
	void move(Point move_direction);
};
