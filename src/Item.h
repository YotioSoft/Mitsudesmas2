#pragma once
#include <header.h>
#include <ImageTools.h>

class Item
{
private:
	// 画像
	Texture texture;

	// アイテムの座標
	Point position = Point(10, 10);

public:
	// コンストラクタ
	Item();
	Item(Image new_image);

	// 描画
	void draw();
	void drawLight();

	// アイテムの位置を設定
	void setPosition(Point set_position);
	
	// アイテムの位置を取得
	Point getPosition();

	// アイテムの移動
	void move(Point move_direction);
};
