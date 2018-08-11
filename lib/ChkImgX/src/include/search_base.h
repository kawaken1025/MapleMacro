/*--------------------------------------------------------------------------
* Structure (Header)
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

namespace chkimg {

struct SearchResult {
	int x, y;
	double diff;
	int number;
};

struct Bitmap {
	int width;
	int height;
	int stride;
	void* scan0;
};

void MakeColorDiffImage(Bitmap rgbImage, Bitmap grayImage, int color);
void GrayToRGBImage(Bitmap grayImage, Bitmap rgbImage);

} // chkimg
