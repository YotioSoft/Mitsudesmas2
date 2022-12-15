#pragma once
#include "header.h"
#include "MapObject.h"
#include "Character.h"

typedef struct Citizen {
	Character character;
	SquarePosition position;
	Point moving = Point(0, 0);
	bool locked_on = false;
} Citizen;

typedef struct Couple {
	Citizen character1;
	Citizen character2;
	bool crowded = true;
	bool locked_on = false;
} Couple;

class GameMap
{
private:
	// �I�u�W�F�N�g
	std::map<String, MapObject> objects;

	// �I�u�W�F�N�g�̃}�b�v
	Array<Array<Array<MapObject>>> objects_map;

	// �}�b�v��̃I�u�W�F�N�g�̌���
	Array<Array<Array<MapChipProfiles::Directions>>> object_directions_map;

	// �v���C���[
	Character player;

	// �}�b�v��̃L�����N�^
	Array<Citizen> soli;
	Array<Couple> couples;

	// ���S���W
	SquarePosition center_square;

	// ���W�̃I�t�Z�b�g�i-32?32�j
	Point square_position_offset = Point(0, 0);
	
	// �ړ����x�����[�h
	bool slow_mode = false;

public:
	// �}�b�v�o�^
	GameMap();
	GameMap(Array<Array<Array<MapObject>>> init_objects_map,
		Array<Array<Array<MapChipProfiles::Directions>>> init_object_directions_map,
		Character init_player,
		SquarePosition init_center_square);
	GameMap(FilePath map_file_path,
		std::map<String, MapObject> init_objects,
		Character init_player,
		SquarePosition init_center_square);
	
	// �L�����N�^�[�̐ݒu
	void putCharacter(Citizen character);
	void putCouple(Couple couple);
	
	// �ʍs�\���ۂ�
	bool isPassable(SquarePosition position);
	
	// ���W��ɂ���L�����N�^�[���擾
	Character* getCharacter(SquarePosition position);
	Couple* getCouple(SquarePosition position);

	// ���_���ړ�
	SquarePosition moveCamera(Point direction);
	
	// �ړ��̑����̐ݒ�
	void setSlowMode(bool enable);
	
	// �L�����N�^�[�̊Ԃ��󂯂�
	int space();
	
	// �}�b�v�T�C�Y���擾
	Size getMapSize();

	// �}�b�v�`��
	void draw();

	// �`�b�v�̍��W�����ʏ�̍��W�ɕϊ�
	Point squarePositionToPoint(SquarePosition square_position);

	// ��ʏ�̍��W����`�b�v�̍��W�ɕϊ�
	SquarePosition pointToSquarePosition(Point point);

	// ���͂̓������o���w�肳�ꂽ�}�X�̓��̌���������
	MapChipProfiles::Directions setConnectableObjectDirection(SquarePosition square_position, MapChipProfiles::Types type, int max_size);
	MapChipProfiles::Directions setUnconnectableObjectDirection(SquarePosition square_position, MapObject object);

	// �}�b�v�ǂݍ���
	void load(FilePath file_path);

	// �}�b�v�ۑ�
	void save(FilePath file_path);
};
