#pragma once
#include "header.h"

namespace ImageTools {
	// Image��2�{�ɂ���
	Image zoomImage2x(Image& original);
	Image zoomImage4x(Image& original);

	// �ԍ�����摜��̍��W�ɕϊ�
	// �ԍ��͍��ォ�牡������1�����Ɋ��蓖�Ă��Ă���
	Point getObjectPositionOnImage(const int number, const Size chip_size, const int chips_in_a_row);
}
