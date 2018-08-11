/*--------------------------------------------------------------------------
* Structure (Header)
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#include "search_base.h"

namespace chkimg {

/*--------------------------------------------------------------------------
* Gray Image
*--------------------------------------------------------------------------*/

// 指定した色とどれだけ近いかでGray化
void MakeColorDiffImage(Bitmap rgbImage, Bitmap grayImage, int color) {
	uint8_t* img = (uint8_t*)rgbImage.scan0;
	const int iw = rgbImage.width;
	const int ih = rgbImage.height;
	const int is = rgbImage.stride;
	uint8_t* gray = (uint8_t*)grayImage.scan0;
	const int gs = grayImage.stride;

	int r = (color >> 16) & 0xFF;
	int g = (color >>  8) & 0xFF;
	int b = (color >>  0) & 0xFF;

	for(int y = 0; y < ih; ++y) {
		for(int x = 0; x < iw; ++x) {
			int offset = 3 * x + is * y;
			// ビットマップの色の並びは B G R なので注意！（RGBではない）
			int diff = std::abs(int(img[offset + 2]) - r) +
				std::abs(int(img[offset + 1]) - g) +
				std::abs(int(img[offset + 0]) - b);
			gray[x + gs * y] = std::min(diff, 255);
		}
	}
}

// グレースケールをRGB化
void GrayToRGBImage(Bitmap grayImage, Bitmap rgbImage) {
	uint8_t* img = (uint8_t*)rgbImage.scan0;
	const int iw = rgbImage.width;
	const int ih = rgbImage.height;
	const int is = rgbImage.stride;
	uint8_t* gray = (uint8_t*)grayImage.scan0;
	const int gs = grayImage.stride;

	for(int y = 0; y < ih; ++y) {
		for(int x = 0; x < iw; ++x) {
			int offset = 3 * x + is * y;
			img[offset + 0] = img[offset + 1] = img[offset + 2] = gray[x + gs * y];
		}
	}
}

} // chkimg
