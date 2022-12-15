#pragma once
#include "header.h"
#include "ImageTools.h"
#include "MapChipProfiles.h"

class MapChip
{
private:
	// �e�N�X�`��
	Texture texture;

	// �`�b�v�̎��
	MapChipProfiles::Types type;

	// �`�b�v�̌����̑���
	bool directiond_exist;

	// �`�b�v�̌���
	MapChipProfiles::Directions direction;

	// �L�����N�^�[�̒ʍs�̉�
	bool passable;

public:
	// �R���X�g���N�^
	MapChip(Image &chip_image, int init_position_number, MapChipProfiles::Types init_type, MapChipProfiles::Directions init_direction, bool init_passable);

	// ����
	MapChipProfiles::Directions getDirection();

	// �ʍs�̉�
	bool isPassable();

	// ���
	MapChipProfiles::Types getType();

	// �`��
	void draw(Point position);
	void draw(SquarePosition sposition);
};
