#include <header.h>
#include <Character.h>
#include <LoadFiles.h>
#include <GameMap.h>

void Main();

typedef struct MapStruct {
	GameMap game_map;
	Duration remining_time;
	int rest;
	Color font_color;
	FilePath bgm_path;
	
	MapStruct() {}
	MapStruct(GameMap& init_map, Duration init_remining, int init_rest, Color init_font_color, FilePath init_bgm_path) {
		game_map = init_map;
		remining_time = init_remining;
		rest = init_rest;
		font_color = init_font_color;
		bgm_path = init_bgm_path;
	}
} MapStruct;

// タイトル画面
int TitleMenu(std::map<String, std::map<String, Array<Character>>>& characters) {
	// 画像の読み込み
	Texture logo_img(Unicode::Widen(CURRENT_DIR) + U"/img/logo.png");
	
	const Font font15(15);
	
	bool show_stages = false;
    
    auto copyright = font15(U"(C) YotioSoft 2020-2022");

	int count = 0;
	while (System::Update())
	{
		logo_img.draw(Scene::Width()/2 - logo_img.width()/2, 50);
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
		
		copyright.draw(Scene::Width()/2 - copyright.region(0, 0).size.x/2, Scene::Height()-40, TITLE_FONT_COLOR);

		count++;
	}
	
	return 0;
}

int HowToPlay() {
	// フォントを用意
	const Font font20(20);
	const Font font40(40);
	const Font font60(60);

	while (System::Update())
	{
		font60(U"あそびかた").draw(30, 10, TITLE_FONT_COLOR);

		font40(U"ルール").draw(30, 100, TITLE_FONT_COLOR);
		font20(U"密になっているカップルに「密です」といい距離を開けてもらいます。\n時間内にマップ上のすべてのカップルが距離を開けたらゲームクリアです。\nすでに距離を開けているカップルや、カップルじゃない人に「密です」というと\n怒られ、MPが減ります。4回怒られたらゲームオーバーです。\nHPが0になると歩き方が遅くなります。").draw(30, 150, TITLE_FONT_COLOR);

		font40(U"操作方法").draw(30, 300, TITLE_FONT_COLOR);
		font20(U"←↑↓→  ：マップ上を移動する\nSPACEキー：「密です」という").draw(30, 350, TITLE_FONT_COLOR);

		font20(U"フリー素材・ライブラリ情報は              　をご覧ください。").draw(30, 450, TITLE_FONT_COLOR);

		if (SimpleGUI::Button(U"こちら", Vec2(30 + font20(U"フリー素材・ライブラリ情報は").region(Point(30, 400)).size.x, 440))) {
			return 1;
		}

		if (SimpleGUI::Button(U"タイトルへ", Vec2(Scene::Width() / 2 - 70, Scene::Height() - 100))) {
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
		font40(U"フリー素材・ライブラリ情報").draw(30, 10, TITLE_FONT_COLOR);

		font15(str).draw(30, 60, TITLE_FONT_COLOR);

		if (SimpleGUI::Button(U"もどる", Vec2(Scene::Width() / 2 - 60, Scene::Height() - 100))) {
			return;
		}
	}
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

// 拡声器の配置
void putSpeakers(GameMap& game_map, std::map<String, Array<Item>>& items, int total_speakers) {
	int count = 0;
	while (count < total_speakers) {
		SquarePosition man_pos = SquarePosition(Random(0, game_map.getMapSize().x-1), Random(0, game_map.getMapSize().y-1));
		bool can_put = true;
		if (man_pos.x < 0 || man_pos.x > game_map.getMapSize().x - 1) {
			continue;
		}
			
		if (!game_map.isPassable(man_pos)) {
			can_put = false;
		}
		
		PlacedItem item;
		item.item = items[U"speaker"].choice(1)[0];
		item.position = man_pos;
		
		if (!game_map.isPassable(item.position)) {
			continue;
		}
		
		game_map.putSpeaker(item);
		
		count ++;
	}
}

// HP回復用の食べ物の配置
void putFoods(GameMap& game_map, std::map<String, Array<Item>>& items, int total_speakers) {
	int count = 0;
	while (count < total_speakers) {
		SquarePosition man_pos = SquarePosition(Random(0, game_map.getMapSize().x - 1), Random(0, game_map.getMapSize().y - 1));
		bool can_put = true;
		if (man_pos.x < 0 || man_pos.x > game_map.getMapSize().x - 1) {
			continue;
		}

		if (!game_map.isPassable(man_pos)) {
			can_put = false;
		}

		PlacedItem item;
		item.item = items[U"chicken"].choice(1)[0];
		item.position = man_pos;

		if (!game_map.isPassable(item.position)) {
			continue;
		}

		game_map.putFood(item);

		count++;
	}
}

// 残り時間追加用の時計の配置
void putWatches(GameMap& game_map, std::map<String, Array<Item>>& items, int total_speakers) {
	int count = 0;
	while (count < total_speakers) {
		SquarePosition man_pos = SquarePosition(Random(0, game_map.getMapSize().x - 1), Random(0, game_map.getMapSize().y - 1));
		bool can_put = true;
		if (man_pos.x < 0 || man_pos.x > game_map.getMapSize().x - 1) {
			continue;
		}

		if (!game_map.isPassable(man_pos)) {
			can_put = false;
		}

		PlacedItem item;
		item.item = items[U"watch"].choice(1)[0];
		item.position = man_pos;

		if (!game_map.isPassable(item.position)) {
			continue;
		}

		game_map.putWatch(item);

		count++;
	}
}

void Game(MapStruct& map_struct, std::map<String, MapObject>& map_objects, 
	std::map<String, std::map<String, Array<Character>>>& characters, std::map<String, Array<Item>>& items) {
	// 背景色
	Scene::SetBackground(Palette::Lightskyblue);

	// フォントを用意
	const Font font(20);
	const Font font60(60);
	
	// ゲージ
	double HP = 100;
	
	// 残りのカップル数
	int rest = map_struct.rest;
	int init_rest = rest;

	// 残りの拡声器
	int rest_speakers = rest;
	
	// マップの読み込み
	GameMap game_map = map_struct.game_map;
	
	// キャラクターの配置
	putNormies(game_map, characters, rest);
	putSpacedNormies(game_map, characters, 10);
	putSoli(game_map, characters, 10);
	putSpeakers(game_map, items, rest * 2);
	putFoods(game_map, items, 10);
	putWatches(game_map, items, 5);
	
	// 画像の読み込み
	Texture img_mitsudesu(Unicode::Widen(CURRENT_DIR) + U"/img/密です.png");
	Texture img_mistake(Unicode::Widen(CURRENT_DIR) + U"/img/mistake.png");
	Texture img_speaker(Unicode::Widen(CURRENT_DIR) + U"/img/charactors/items/speaker.png");
	
	// 音声の読み込み
	Audio audio_mitsudesu(Unicode::Widen(CURRENT_DIR) + U"/audio/handgun-firing1.mp3");
	Audio audio_move(Unicode::Widen(CURRENT_DIR) + U"/audio/bomb1.mp3");
	Audio audio_mistake(Unicode::Widen(CURRENT_DIR) + U"/audio/boyoyon1.mp3");
	Audio audio_bgm(map_struct.bgm_path, Loop::Yes);
	
	// タイマー
	Timer timer(map_struct.remining_time);

	int count = 0;
	int img_mitsudesu_show_count = 0;
	int img_mistake_show_count = 0;
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

			// 拡声器GET
			if (game_map.isThereSpeaker()) {
				game_map.removeCenterSpeaker();
				rest_speakers++;
			}

			// 食べ物でHP回復
			if (game_map.isThereFood()) {
				game_map.removeCenterFood();
				HP += 20;
			}

			// 腕時計で時間追加（+10秒）
			if (game_map.isThereWatch()) {
				game_map.removeCenterWatch();
				timer.setRemaining(Duration(timer.s() + 10));
			}
		}
		
		if (HP <= 1.0) {
			game_map.setSlowMode(true);
		}
		else {
			game_map.setSlowMode(false);
		}
		
		// 「密です」
		if (KeySpace.down() && rest_speakers > 0) {
			rest_speakers--;
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
				img_mistake_show_count = 1;
				
				audio_mistake.playOneShot();
			}
		}
		
		if (img_mitsudesu_show_count >= 1) {
			img_mitsudesu.draw(Scene::Center().x-img_mitsudesu.width()/2, Scene::Center().y-img_mitsudesu.height()/2);
			img_mitsudesu_show_count ++;
			
			if (img_mitsudesu_show_count > 50) {
				img_mitsudesu_show_count = 0;
			}
		}
		if (img_mistake_show_count >= 1) {
			img_mitsudesu.draw(Scene::Center().x-img_mitsudesu.width()/2, Scene::Center().y-img_mitsudesu.height()/2);
			img_mistake.draw(Scene::Center().x-img_mistake.width()/2-18, Scene::Center().y-img_mistake.height()/2-30);
			img_mistake_show_count ++;
			
			if (img_mistake_show_count > 50) {
				img_mistake_show_count = 0;
			}
		}
		
		// ゲージの表示
		font(U"HP").draw(10, 10, Color(map_struct.font_color));
		Rect(50, 10, HP * 1.5, 20).draw(Color(Palette::Skyblue));
		Rect(HP * 1.5 + 50, 10, 100 * 1.5 - HP * 1.5, 20).draw(Color(Palette::Gray));

		// 残り拡声器数
		img_speaker.resized(32, 32).draw(10, 50);
		font(U"{}"_fmt(rest_speakers)).draw(50, 50, Color(map_struct.font_color));
		
		// 情報の表示
		font(U"残り " + Format(rest) + U"組").draw(Scene::Width()-150, 10, Color(map_struct.font_color));
		font(U"TIME " + Format(timer.s()) + U"s").draw(Scene::Width()-150, 50, Color(map_struct.font_color));
		
		// ゲームオーバー判定
		if (timer.ms() == 0.0) {
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
		
		// 結果発表
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
				Game(map_struct, map_objects, characters, items);
			}
			if (SimpleGUI::Button(U"もどる", Vec2(Scene::Width()/2-60, Scene::Height()-100))) {
				audio_bgm.stop();
				return;
			}
		}

		count++;
	}
}

void Main() {
	std::cout << Unicode::Widen(CURRENT_DIR) << std::endl;
	Window::SetTitle(U"ミツデスマス2");
	
	// 背景色
	Scene::SetBackground(Palette::Lightgreen);
	Scene::SetTextureFilter(TextureFilter::Nearest);
	
	// マップオブジェクトの読み込み
	std::map<String, MapObject> map_objects = LoadFiles::InitMapObjects();

	// キャラクターの読み込み
	std::map<String, std::map<String, Array<Character>>> characters = LoadFiles::InitCharacters();
	std::map<String, Array<Item>> items = LoadFiles::InitItems();
	
	// MapStructを作成
	GameMap map1(Unicode::Widen(CURRENT_DIR) + U"/data/maps/map1.csv", map_objects, characters[U"man"][U"player"][0], SquarePosition(15, 15));
	MapStruct stage1(map1, Duration(90), 20, Color(Palette::White), Unicode::Widen(CURRENT_DIR) + U"/audio/bgm_stage1.mp3");
	
	GameMap map2(Unicode::Widen(CURRENT_DIR) + U"/data/maps/map2.csv", map_objects, characters[U"man"][U"player"][0], SquarePosition(15, 15));
	MapStruct stage2(map2, Duration(240), 20, Color(Palette::White), Unicode::Widen(CURRENT_DIR) + U"/audio/bgm_stage2.mp3");
	
	GameMap map3(Unicode::Widen(CURRENT_DIR) + U"/data/maps/map3.csv", map_objects, characters[U"man"][U"player"][0], SquarePosition(15, 15));
	MapStruct stage3(map3, Duration(600), 40, Color(Palette::Black), Unicode::Widen(CURRENT_DIR) + U"/audio/bgm_stage3.mp3");
	
	// タイトル画面
	while(System::Update()) {
		switch (TitleMenu(characters)) {
			case 0:
				if (HowToPlay() == 1) {
					ReadMe();
				}
				break;
			case 1:
				Game(stage1, map_objects, characters, items);
				break;
			case 2:
				Game(stage2, map_objects, characters, items);
				break;
			case 3:
				Game(stage3, map_objects, characters, items);
				break;
		}
	}
}
