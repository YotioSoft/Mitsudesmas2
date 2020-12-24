#include "header.h"
#include "Character.h"
#include "LoadFiles.h"
#include "GameMap.h"

void Main();

typedef struct MapStruct {
	GameMap game_map;
	int remining_time;
	int rest;
	Color font_color;
	
	MapStruct() {}
	MapStruct(GameMap& init_map, int init_remining, int init_rest, Color init_font_color) {
		game_map = init_map;
		remining_time = init_remining;
		rest = init_rest;
		font_color = init_font_color;
	}
} MapStruct;

// タイトル画面
int TitleMenu(std::map<String, std::map<String, Array<Character>>>& characters) {
	// 画像の読み込み
	Texture logo_img(Unicode::Widen(CURRENT_DIR) + U"/img/logo.png");
	
	const Font font15(15);
	
	bool show_stages = false;

	int count = 0;
	while (System::Update())
	{
		logo_img.draw(Scene::Width()/2- logo_img.width()/2, 100);
		characters[U"man"][U"player"][0].draw();

		if (count % 5 == 0) {
			if (KeyUp.pressed()) {
				characters[U"man"][U"player"][0].walk(Direction::TOP);
			}
			else if (KeyLeft.pressed()) {
				characters[U"man"][U"player"][0].walk(Direction::LEFT);
			}
			else if (KeyRight.pressed()) {
				characters[U"man"][U"player"][0].walk(Direction::RIGHT);
			}
			else if (KeyDown.pressed()) {
				characters[U"man"][U"player"][0].walk(Direction::BOTTOM);
			}
		}

		if (show_stages) {
			if (SimpleGUI::Button(U"Stage1.大きな公園", Vec2(Scene::Width()/2-110, Scene::Height()-250))) {
				return 1;
			}
			if (SimpleGUI::Button(U"Stage2.山中の平野", Vec2(Scene::Width()/2-110, Scene::Height()-200))) {
				return 2;
			}
			if (SimpleGUI::Button(U"Stage3.雪の降る街", Vec2(Scene::Width()/2-110, Scene::Height()-150))) {
				return 3;
			}
			if (SimpleGUI::Button(U"もどる", Vec2(Scene::Width()/2-60, Scene::Height()-100))) {
				show_stages = false;
			}
		}
		else {
			if (SimpleGUI::Button(U"はじめる", Vec2(Scene::Width()/2-60, Scene::Height()-150))) {
				show_stages = true;
			}
			if (SimpleGUI::Button(U"遊びかた", Vec2(Scene::Width()/2-60, Scene::Height()-100))) {
				return 0;
			}
		}
		
		font15(U"(C) YotioSoft 2020").draw(Scene::Width()/2 - font15(U"(C) YotioSoft 2020").region(0, 0).size.x/2, Scene::Height()-40);

		count++;
	}
	
	return 0;
}

// リア充の配置
void putNormies(GameMap& game_map, std::map<String, std::map<String, Array<Character>>>& characters, int total_couples) {
	int count = 0;
	while (count < total_couples) {
		String type;
		if (RandomBool(0.5)) {
			type = U"youth";
		} else {
			type = U"normal";
		}
		
		SquarePosition man_pos = SquarePosition(Random(0, game_map.getMapSize().x-2), Random(0, game_map.getMapSize().y-1));
		bool can_put = true;
		for (int x=man_pos.x-4; x<=man_pos.x+5; x++) {
			if (x < 0 || x > game_map.getMapSize().x - 1) {
				continue;
			}
			
			if (!game_map.isPassable(SquarePosition(x, man_pos.y))) {
				can_put = false;
			}
		}
		if (!can_put) {
			continue;
		}
		
		Citizen man;
		man.character = characters[U"man"][type].choice(1)[0];
		man.position = man_pos;
		
		if (!game_map.isPassable(man.position)) {
			continue;
		}
		
		Citizen woman;
		woman.character = characters[U"woman"][type].choice(1)[0];
		woman.position = SquarePosition(man.position.x + 1, man.position.y);
		
		if (!game_map.isPassable(woman.position)) {
			continue;
		}
		
		Couple couple;
		couple.character1 = man;
		couple.character2 = woman;
		couple.crowded = true;
		
		game_map.putCouple(couple);
		
		count ++;
	}
}

// 距離を開けてるリア充の配置
void putSpacedNormies(GameMap& game_map, std::map<String, std::map<String, Array<Character>>>& characters, int total_couples) {
	int count = 0;
	while (count < total_couples) {
		String type;
		if (RandomBool(0.5)) {
			type = U"youth";
		} else {
			type = U"normal";
		}
		
		SquarePosition man_pos = SquarePosition(Random(0, game_map.getMapSize().x-2), Random(0, game_map.getMapSize().y-1));
		bool can_put = true;
		for (int x=man_pos.x; x<=man_pos.x+3; x++) {
			if (x < 0 || x > game_map.getMapSize().x - 1) {
				continue;
			}
			
			if (!game_map.isPassable(SquarePosition(x, man_pos.y))) {
				can_put = false;
			}
		}
		if (!can_put) {
			continue;
		}
		
		Citizen man;
		man.character = characters[U"man"][type].choice(1)[0];
		man.position = man_pos;
		
		if (!game_map.isPassable(man.position)) {
			continue;
		}
		
		Citizen woman;
		woman.character = characters[U"woman"][type].choice(1)[0];
		woman.position = SquarePosition(man.position.x + 3, man.position.y);
		
		if (!game_map.isPassable(woman.position)) {
			continue;
		}
		
		Couple couple;
		couple.character1 = man;
		couple.character2 = woman;
		couple.crowded = false;
		
		game_map.putCouple(couple);
		
		count ++;
	}
}

// ソロ充の位置
void putSoli(GameMap& game_map, std::map<String, std::map<String, Array<Character>>>& characters, int total_soli) {
	int count = 0;
	while (count < total_soli) {
		String type;
		if (RandomBool(0.5)) {
			type = U"man";
		} else {
			type = U"woman";
		}
		
		SquarePosition man_pos = SquarePosition(Random(0, game_map.getMapSize().x-1), Random(0, game_map.getMapSize().y-1));
		bool can_put = true;
		if (man_pos.x < 0 || man_pos.x > game_map.getMapSize().x - 1) {
			continue;
		}
			
		if (!game_map.isPassable(man_pos)) {
			can_put = false;
		}
		
		Citizen man;
		man.character = characters[type][U"solo"].choice(1)[0];
		man.position = man_pos;
		
		if (!game_map.isPassable(man.position)) {
			continue;
		}
		
		game_map.putCharacter(man);
		
		count ++;
	}
}

void Game(MapStruct& map_struct, std::map<String, MapObject>& map_objects, std::map<String, std::map<String, Array<Character>>>& characters) {
	// フォントを用意
	const Font font(20);
	const Font font60(60);
	
	// ゲージ
	double HP = 100;
	double MP = 100;
	
	// 残りのカップル数
	int rest = map_struct.rest;
	int init_rest = rest;
	
	// マップの読み込み
	GameMap game_map = map_struct.game_map;
	
	// キャラクターの配置
	putNormies(game_map, characters, rest);
	putSpacedNormies(game_map, characters, 10);
	putSoli(game_map, characters, 10);
	
	// 画像の読み込み
	Texture img_mitsudesu(Unicode::Widen(CURRENT_DIR) + U"/img/密です.png");
	Texture img_chigaudaro(Unicode::Widen(CURRENT_DIR) + U"/img/ちーがーうーだーろー.png");
	
	// 音声の読み込み
	Audio audio_mitsudesu(Unicode::Widen(CURRENT_DIR) + U"/audio/handgun-firing1.mp3");
	Audio audio_move(Unicode::Widen(CURRENT_DIR) + U"/audio/bomb1.mp3");
	Audio audio_chigaudaro(Unicode::Widen(CURRENT_DIR) + U"/audio/boyoyon1.mp3");
	Audio audio_bgm(Unicode::Widen(CURRENT_DIR) + U"/audio/hawk_eye.mp3", Arg::loop = true);
	
	// タイマー
	Timer timer(map_struct.remining_time);

	int count = 0;
	int img_mitsudesu_show_count = 0;
	int img_chigaudaro_show_count = 0;
	bool game_enable = true;
	bool game_over = false;
	timer.start();
	audio_bgm.play();
	while (System::Update())
	{
		game_map.draw();
		
		bool move = false;
		if (count % 5 == 0 && game_enable) {
			if (KeyUp.pressed()) {
				game_map.moveCamera(Direction::TOP);
				move = true;
			}
			else if (KeyLeft.pressed()) {
				game_map.moveCamera(Direction::LEFT);
				move = true;
			}
			else if (KeyRight.pressed()) {
				game_map.moveCamera(Direction::RIGHT);
				move = true;
			}
			else if (KeyDown.pressed()) {
				game_map.moveCamera(Direction::BOTTOM);
				move = true;
			}
			
			if (move) {
				if (HP >= 0.1) {
					HP -= 0.1;
				}
			}
			
			if (!move && HP <= 99.8) {
				HP += 0.2;
			}
		}
		
		if (HP <= 1.0) {
			game_map.setSlowMode(true);
		}
		else {
			game_map.setSlowMode(false);
		}
		
		if (KeySpace.down()) {
			audio_mitsudesu.playOneShot();
			int mitsu = game_map.space();
			
			// 密だった
			if (mitsu == Result::SUCCESS) {
				rest -= 1;
				img_mitsudesu_show_count = 1;
				
				audio_move.playOneShot();
			}
			// 密じゃなかった
			else if (mitsu == Result::FAILURE) {
				MP -= 25;
				img_chigaudaro_show_count = 1;
				
				audio_chigaudaro.playOneShot();
			}
		}
		
		if (img_mitsudesu_show_count >= 1) {
			img_mitsudesu.draw(Scene::Width()/2-128, Scene::Height()/2-150);
			img_mitsudesu_show_count ++;
			
			if (img_mitsudesu_show_count > 50) {
				img_mitsudesu_show_count = 0;
			}
		}
		if (img_chigaudaro_show_count >= 1) {
			img_mitsudesu.draw(Scene::Width()/2-128, Scene::Height()/2-150);
			img_chigaudaro.draw(Scene::Width()/2-110, Scene::Height()/2-120);
			img_chigaudaro_show_count ++;
			
			if (img_chigaudaro_show_count > 50) {
				img_chigaudaro_show_count = 0;
			}
		}
		
		// ゲージの表示
		font(U"HP").draw(10, 10, Color(map_struct.font_color));
		Rect(50, 10, HP * 1.5, 20).draw(Color(Palette::Skyblue));
		Rect(HP * 1.5 + 50, 10, 100 * 1.5 - HP * 1.5, 20).draw(Color(Palette::Gray));
		
		font(U"MP").draw(10, 50, Color(map_struct.font_color));
		Rect(50, 50, MP * 1.5, 20).draw(Color(Palette::Lightblue));
		Rect(MP * 1.5 + 50, 50, 100 * 1.5 - MP * 1.5, 20).draw(Color(Palette::Gray));
		
		// 情報の表示
		font(U"残り " + Format(rest) + U"組").draw(Scene::Width()-150, 10, Color(map_struct.font_color));
		font(U"TIME " + Format(timer.s()) + U"sec.").draw(Scene::Width()-150, 50, Color(map_struct.font_color));
		
		// ゲームオーバー判定
		if (timer.ms() == 0.0 || MP <= 0.0) {
			timer.pause();
			game_enable = false;
			game_over = true;
		}
		
		// ゲームクリア判定
		if (rest == 0) {
			timer.pause();
			game_enable = false;
			game_over = false;
		}
		
		if (!game_enable) {
			Rect(0, 0, Scene::Width(), Scene::Height()).draw(Color(50, 50, 50, 200));
			
			if (game_over) {
				font60(U"ゲームオーバー").draw(Scene::Width()/2-font60(U"ゲームオーバー").region(Point(0, 0)).size.x/2, Scene::Height()/2-150, Color(Palette::White));
			} else {
				font60(U"ゲームクリア").draw(Scene::Width()/2-font60(U"ゲームクリア").region(Point(0, 0)).size.x/2, Scene::Height()/2-150, Color(Palette::White));
			}
			font(U"距離を開けたカップルの数：" + Format(init_rest - rest) + U"組").draw(Scene::Width()/2-font(U"距離を開けたカップルの数：" + Format(init_rest - rest) + U"組").region(Point(0, 0)).size.x/2, Scene::Height()/2, Color(Palette::White));
			font(U"残り時間：" + Format(timer.s()) + U"秒").draw(Scene::Width()/2-font(U"残り時間：" + Format(timer.s()) + U"秒").region(Point(0, 0)).size.x/2, Scene::Height()/2+50, Color(Palette::White));
			
			if (SimpleGUI::Button(U"もう一度", Vec2(Scene::Width()/2-70, Scene::Height()-150))) {
				audio_bgm.stop();
				Game(map_struct, map_objects, characters);
			}
			if (SimpleGUI::Button(U"もどる", Vec2(Scene::Width()/2-60, Scene::Height()-100))) {
				audio_bgm.stop();
				return;
			}
		}

		count++;
	}
}

int HowToPlay() {
	// フォントを用意
	const Font font20(20);
	const Font font40(40);
	const Font font60(60);
	
	while (System::Update())
	{
		font60(U"あそびかた").draw(30, 10);
		
		font40(U"ルール").draw(30, 100);
		font20(U"密になっているカップルに「密です」といい距離を開けてもらいます。\n時間内にマップ上のすべてのカップルが距離を開けたらゲームクリアです。\nすでに距離を開けているカップルや、カップルじゃない人に「密です」というと\n怒られ、MPが減ります。4回怒られたらゲームオーバーです。\nHPが0になると歩き方が遅くなります。").draw(30, 150);
		
		font40(U"操作方法").draw(30, 300);
		font20(U"←↑↓→  ：マップ上を移動する\nSPACEキー：「密です」という").draw(30, 350);
		
		font20(U"フリー素材・ライブラリ情報は               　　をご覧ください。").draw(30, 450);
		
		if (SimpleGUI::Button(U"こちら", Vec2(30 + font20(U"フリー素材・ライブラリ情報は").region(Point(30, 400)).size.x, 440))) {
			return 1;
		}
		
		if (SimpleGUI::Button(U"タイトルへ", Vec2(Scene::Width()/2-70, Scene::Height()-100))) {
			break;
		}
	}
	return 2;
}

void ReadMe() {
	// フォントを用意
	const Font font15(15);
	const Font font40(40);
	
	TextEditState tes;
	
	TextReader reader(Unicode::Widen(CURRENT_DIR) + U"/sozai.txt");
	String str, line;
	
	while (reader.readLine(line)) {
		str += line + U"\n";
	}
	
	while (System::Update())
	{
		font40(U"フリー素材・ライブラリ情報").draw(30, 10);
		
		font15(str).draw(30, 60);
		
		if (SimpleGUI::Button(U"もどる", Vec2(Scene::Width()/2-60, Scene::Height()-100))) {
			return;
		}
	}
}

void Main() {
	std::cout << Unicode::Widen(CURRENT_DIR) << std::endl;
	Window::SetTitle(U"ミツデスマス");
	
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.5, 0.7, 0.9));
	Scene::SetTextureFilter(TextureFilter::Nearest);
	
	// マップオブジェクトの読み込み
	std::map<String, MapObject> map_objects = LoadFiles::InitMapObjects();

	// キャラクターの読み込み
	std::map<String, std::map<String, Array<Character>>> characters = LoadFiles::InitCharacters();
	
	// MapStructを作成
	GameMap map1(Unicode::Widen(CURRENT_DIR) + U"/data/maps/map1.rpgmap", map_objects, characters[U"man"][U"player"][0], SquarePosition(15, 15));
	MapStruct stage1(map1, 90, 20, Color(Palette::White));
	
	GameMap map2(Unicode::Widen(CURRENT_DIR) + U"/data/maps/map2.rpgmap", map_objects, characters[U"man"][U"player"][0], SquarePosition(15, 15));
	MapStruct stage2(map2, 240, 20, Color(Palette::White));
	
	GameMap map3(Unicode::Widen(CURRENT_DIR) + U"/data/maps/map3.rpgmap", map_objects, characters[U"man"][U"player"][0], SquarePosition(15, 15));
	MapStruct stage3(map3, 600, 40, Color(Palette::Black));
	
	// タイトル画面
	while(System::Update()) {
		switch (TitleMenu(characters)) {
			case 0:
				if (HowToPlay() == 1) {
					ReadMe();
				}
				break;
			case 1:
				Game(stage1, map_objects, characters);
				break;
			case 2:
				Game(stage2, map_objects, characters);
				break;
			case 3:
				Game(stage3, map_objects, characters);
				break;
		}
	}
}
