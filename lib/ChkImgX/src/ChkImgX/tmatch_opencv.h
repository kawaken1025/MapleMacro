/*--------------------------------------------------------------------------
* テンプレートマッチング OpenCVを使った実装
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

namespace chkimg {
	
class MatchTemplateGray {
	enum {
		MAX_MATCH_POINTS = 256,
	};
public:
	void init(Bitmap img) {
		imgData = img;
	}
	std::vector<SearchResult>& search(Bitmap ref, double diff_limit);

private:
	Bitmap imgData;
	std::vector<SearchResult> result;
};
	
class MatchTemplateRGB {
	enum {
		MAX_MATCH_POINTS = 256,
	};
public:
	void init(Bitmap img) {
		imgData = img;
		imgBGR.clear();
		split_bitmap(imgBGR, imgData);
	}
	std::vector<SearchResult>& search(Bitmap ref, double diff_limit);

private:
	Bitmap imgData;
	std::vector<cv::Mat> imgBGR;
	std::vector<SearchResult> result;

	static void split_bitmap(std::vector<cv::Mat>& bgr, const Bitmap& img);
};

}
