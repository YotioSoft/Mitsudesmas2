#include "header.h"
#include "Character.h"
#include "LoadFiles.h"
#include "GameMap.h"

void TitleMenu() {
	// 画像の読み込み
	std::map<String, Texture> textures = LoadFiles::InitTextures();

	// キャラクターの読み込み
	std::map<String, Character> characters = LoadFiles::InitCharacters();

	// マップオブジェクトの読み込み
	std::map<String, MapObject> map_objects = LoadFiles::InitMapObjects();

	int count = 0;
	while (System::Update())
	{
		textures[U"logo"].draw(Scene::Width()/2- textures[U"logo"].width()/2, 100);
		characters[U"player"].draw();

		if (count % 5 == 0) {
			if (KeyUp.pressed()) {
				characters[U"player"].walk(Direction::TOP);
			}
			else if (KeyLeft.pressed()) {
				characters[U"player"].walk(Direction::LEFT);
			}
			else if (KeyRight.pressed()) {
				characters[U"player"].walk(Direction::RIGHT);
			}
			else if (KeyDown.pressed()) {
				characters[U"player"].walk(Direction::BOTTOM);
			}
		}
		std::cout << "coutだよーん" << std::endl;
		std::cout << map_objects[U"gravel"].draw(MapChipProfiles::Directions::None, Point(10, 10)) << std::endl;

		if (SimpleGUI::Button(U"はじめる", Vec2(Scene::Width()/2-50, Scene::Height()-150)))
		{
			return;
		}

		count++;
	}
}

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	Scene::SetTextureFilter(TextureFilter::Nearest);

	// 大きさ 60 のフォントを用意
	const Font font(60);

	TitleMenu();

	// マップオブジェクトの読み込み
	std::map<String, MapObject> map_objects = LoadFiles::InitMapObjects();

	// キャラクターの読み込み
	std::map<String, Character> characters = LoadFiles::InitCharacters();

	GameMap map1(U"./data/maps/map1.rpgmap", map_objects, characters[U"player"], SquarePosition(1, 1));

	int count = 0;
	while (System::Update())
	{
		map1.draw();

		if (count % 5 == 0) {
			if (KeyUp.pressed()) {
				SquarePosition sp = map1.moveCamera(Direction::TOP);
				font(U"{},{}"_fmt(sp.x, sp.y)).draw(10, 10);
			}
			else if (KeyLeft.pressed()) {
				SquarePosition sp = map1.moveCamera(Direction::LEFT);
				font(U"{},{}"_fmt(sp.x, sp.y)).draw(10, 10);
			}
			else if (KeyRight.pressed()) {
				SquarePosition sp = map1.moveCamera(Direction::RIGHT);
				font(U"{},{}"_fmt(sp.x, sp.y)).draw(10, 10);
			}
			else if (KeyDown.pressed()) {
				SquarePosition sp = map1.moveCamera(Direction::BOTTOM);
				font(U"{},{}"_fmt(sp.x, sp.y)).draw(10, 10);
			}
		}

		Circle(Scene::Width()/2, Scene::Height()/2, 1).draw(Palette::Green);
		count++;
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
