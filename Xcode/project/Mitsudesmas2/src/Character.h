#pragma once
#include "header.h"
#include "ImageTools.h"
#include "CharacterProfiles.h"

class Character
{
private:
	// �摜��̃C���f�b�N�X�i0?11�j
	int index;

	// �L�����N�^�[�̌���
	Point direction;

	// �摜
	Texture texture;

	// �L�����N�^�[�̍��W
	Point position = Point(10, 10);

	// ��ɒ��S���W���H
	bool alwaysCenter;

public:
	// �R���X�g���N�^
	Character();
	Character(Image new_image, const Point init_direction, const bool init_always_center);

	// �`��
	void draw();
	void drawLight();

	// �L�����N�^�[�̈ʒu��ݒ�
	void setPosition(Point set_position);
	
	// �L�����N�^�[�̈ʒu���擾
	Point getPosition();
	
	// �L�����N�^�[�̌���
	Point getDirection();

	// �L�����N�^�[�̓k��
	void walk(Point move_direction);

	// ������A�j���[�V�����𓮂���
	void oneStep();
	
	// �L�����N�^�[�̈ړ�
	void move(Point move_direction);
};
