#pragma once
#include <header.h>
#include <Character.h>
#include <Item.h>
#include <MapObject.h>

namespace LoadFiles
{
	// �L�����N�^�[�̓ǂݍ���
	std::map<String, std::map<String, Array<Character>>>  InitCharacters();

	std::map<String, Array<Item>>  InitItems();

	// �}�b�v�I�u�W�F�N�g�̓ǂݍ���
	std::map<String, MapObject> InitMapObjects();
};

