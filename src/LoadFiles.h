#pragma once
#include "header.h"
#include "Character.h"
#include "MapObject.h"

namespace LoadFiles
{
	// �L�����N�^�[�̓ǂݍ���
	std::map<String, std::map<String, Array<Character>>>  InitCharacters();

	// �}�b�v�I�u�W�F�N�g�̓ǂݍ���
	std::map<String, MapObject> InitMapObjects();
};

