#pragma once
#include "header.h"
#include "Character.h"
#include "MapObject.h"

namespace LoadFiles
{
	// 画像の読み込み
	std::map<String, Texture> InitTextures();

	// キャラクターの読み込み
	std::map<String, Character> InitCharacters();

	// マップオブジェクトの読み込み
	std::map<String, MapObject> InitMapObjects();
};

