#pragma once
#include "header.h"

namespace ImageTools {
	// Image‚ğ2”{‚É‚·‚é
	Image zoomImage2x(Image original);

	// ”Ô†‚©‚ç‰æ‘œã‚ÌÀ•W‚É•ÏŠ·
	// ”Ô†‚Í¶ã‚©‚ç‰¡•ûŒü‚É1‚Â‚¸‚Â‡‚ÉŠ„‚è“–‚Ä‚ç‚ê‚Ä‚¢‚é
	Point getObjectPositionOnImage(const int number, const Size chip_size, const int chips_in_a_row);
}
