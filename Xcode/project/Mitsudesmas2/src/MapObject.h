#pragma once
#include "header.h"
#include "MapChip.h"

class MapObject
{
private:
	// �}�b�v�`�b�v
	Array<MapChip> chips;

	// ���O
	String name;

	// ���
	MapChipProfiles::Types type;
	
	// �I�u�W�F�N�g����̃T�C�Y
	Size size = Size(1, 1);

public:
	// �R���X�g���N�^
	MapObject();
	MapObject(String init_name, MapChipProfiles::Types init_type);
	MapObject(String init_name, MapChipProfiles::Types init_type, MapChip &init_chip);
	MapObject(String init_name, MapChipProfiles::Types init_type, Array<MapChip> &init_chips);

	// MapChip��ǉ�
	void addMapChip(MapChip init_chip);
	
	// �I�u�W�F�N�g�̃T�C�Y��ύX
	void setObjectSize(Size new_size);
	
	// �I�u�W�F�N�g�̃T�C�Y�̎擾
	Size getObjectSize();

	// ���O�̎擾
	String getName();

	// ���ׂĂ̌����̎擾
	Array<MapChipProfiles::Directions> getDirections();

	// ���ׂẴ`�b�v�̃^�C�v
	MapChipProfiles::Types getType();
	
	// �`�b�v��Ԃ�
	MapChip* getChipP(MapChipProfiles::Directions direction);

	// �`��i���ۂ̕`���chips.draw�ōs���j
	bool draw(const MapChipProfiles::Directions direction, const Point position);
};

