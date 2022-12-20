#pragma once
#include <header.h>
#include <ImageTools.h>

class Item
{
private:
	// �摜
	Texture texture;

	// �L�����N�^�[�̍��W
	Point position = Point(10, 10);

public:
	// �R���X�g���N�^
	Item();
	Item(Image new_image);

	// �`��
	void draw();
	void drawLight();

	// �L�����N�^�[�̈ʒu��ݒ�
	void setPosition(Point set_position);
	
	// �L�����N�^�[�̈ʒu���擾
	Point getPosition();
};
