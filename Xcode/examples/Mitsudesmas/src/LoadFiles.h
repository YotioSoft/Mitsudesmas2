#pragma once
#include "header.h"
#include "Character.h"
#include "MapObject.h"

namespace LoadFiles
{
	// キャラクターの読み込み
	std::map<String, std::map<String, Array<Character>>>  InitCharacters();

	// マップオブジェクトの読み込み
	std::map<String, MapObject> InitMapObjects();
};

