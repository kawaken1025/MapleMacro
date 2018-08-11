/*--------------------------------------------------------------------------
* ChkImgX.dll メイン
* 
* created by Nekorabbit
*--------------------------------------------------------------------------*/
#pragma once

#define LWND_NAME_EXT "CHKIMGX_EXT"

#include <stdint.h>
#include "atlsafe.h"
#include <vector>
#include <map>
#include <algorithm>
#include "win_int64.h"
#include "GDICapture.h"
#include "string_buffer.h"
#include "LightWnd.h"

#undef min
#undef max

namespace chkimg {

RECT scale_rect(const RECT* rect, double scale) {
	RECT wrect = *rect;
	wrect.left *= scale; wrect.top *= scale;
	wrect.right *= scale; wrect.bottom *= scale;
	return wrect;
}

class ImageCacheEntry {
	int number_;
	double scale_;
	GDIBitmap* data_;
	int rgb_; // グレースケール画像用
	Bitmap grayImage_;
	GDIBitmap* grayRGBImage_;
	POINT origSize;
public:
	ImageCacheEntry(const char* imgpath, double scale, int number__)
		: number_(number__)
		, scale_(scale)
		, data_(NULL)
		, rgb_(-1)
		, grayRGBImage_(NULL)
	{
		grayImage_.scan0 = NULL;

		// 暗号化ファイルか？
		int len = strlen(imgpath);
		bool decrypt = (imgpath[len-1] == 'x');

		if(scale == 1.0) {
			data_ = new GDIBitmap(imgpath, decrypt);
			origSize.x = data_->ptr()->GetWidth();
			origSize.y = data_->ptr()->GetHeight();
		}
		else {
			// リサイズする
			GDIBitmap orgImage(imgpath, decrypt);
			origSize.x = orgImage().GetWidth();
			origSize.y = orgImage().GetHeight();
			int r_width = orgImage().GetWidth() * scale;
			int r_height = orgImage().GetHeight() * scale;
			data_ = new GDIBitmap(r_width, r_height);
			{
				Gdiplus::Graphics graphics(data_->ptr());
				if(graphics.DrawImage(&orgImage(), 0, 0, r_width, r_height) != Gdiplus::Ok)
					throw_exception("DrawImageに失敗");
			}
		}
	}
	ImageCacheEntry(GDIBitmap* image__, double scale, int number__)
		: number_(number__)
		, scale_(scale)
		, data_(NULL)
		, rgb_(-1)
		, grayRGBImage_(NULL)
	{
		grayImage_.scan0 = NULL;
		if(scale == 1.0) {
			data_ = image__;
			origSize.x = data_->ptr()->GetWidth();
			origSize.y = data_->ptr()->GetHeight();
		}
		else {
			// リサイズする
			origSize.x = image__->ptr()->GetWidth();
			origSize.y = image__->ptr()->GetHeight();
			int r_width = image__->ptr()->GetWidth() * scale;
			int r_height = image__->ptr()->GetHeight() * scale;
			data_ = new GDIBitmap(r_width, r_height);
			{
				Gdiplus::Graphics graphics(data_->ptr());
				if(graphics.DrawImage(image__->ptr(), 0, 0, r_width, r_height) != Gdiplus::Ok)
					throw_exception("DrawImageに失敗");
			}
			delete image__;
		}
	}

	~ImageCacheEntry() {
		clearBinaryImage();
		delete data_; data_ = NULL;
	}

	int number() const { return number_; }
	double scale() const { return scale_; }
	POINT originalSize() const { return origSize; }

	GDIBitmap* data() const { return data_; }

	Bitmap& grayImage(int rgb__) {
		if(grayImage_.scan0 != NULL && rgb_ == rgb__) {
			return grayImage_;
		}
		clearBinaryImage();
		Bitmap rgbImage = data_->data();
		grayImage_.scan0 = new uint8_t[rgbImage.width*rgbImage.height];
		grayImage_.width = rgbImage.width;
		grayImage_.height = rgbImage.height;
		grayImage_.stride = rgbImage.width;
		MakeColorDiffImage(data_->data(), grayImage_, rgb__);
		rgb_ = rgb__;
		return grayImage_;
	}

	GDIBitmap* grayRGBImage(int rgb__) {
		grayImage(rgb__);
		if(grayRGBImage_ != NULL) {
			return grayRGBImage_;
		}
		grayRGBImage_ = grayToGDIImage(grayImage_);
		return grayRGBImage_;
	}

private:
	void clearBinaryImage() {
		delete [] grayImage_.scan0; grayImage_.scan0 = NULL;
		delete grayRGBImage_; grayRGBImage_ = NULL;
	}

	static GDIBitmap* grayToGDIImage(Bitmap grayImage) {
		GDIBitmap* gdiImage = new GDIBitmap(grayImage.width, grayImage.height);
		GrayToRGBImage(grayImage, gdiImage->data());
		return gdiImage;
	}
};

typedef std::vector<ImageCacheEntry*> ImageCache;

class AppContext {
	class GDIStartup {
		ULONG_PTR gdiplusToken;
	public:
		GDIStartup() {
			Gdiplus::GdiplusStartupInput gdiplusStartupInput = Gdiplus::GdiplusStartupInput();
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		}
		~GDIStartup() {
			Gdiplus::GdiplusShutdown(gdiplusToken);
		}
	};
	// この初期化順は重要！
	GDIStartup gdi;
	std::map<std::string, ImageCache> image_cache;
	std::map<std::string, POINT> image_size;
public:
	GDIEncoder enc;
	bool dump_image;
	bool background_mode;

	AppContext()
		: dump_image(false)
		, background_mode(false)
	{
	}

	~AppContext() {
		for(auto it = image_cache.begin(); it != image_cache.end(); ++it) {
			freeImageCache(it->second);
		}
	}

	POINT imageSize(const char* imgpath_) {
		std::vector<std::string> files; fileList(imgpath_, files);
		if(files.size() == 0) {
			throw_exception("指定されたファイルがありません: %s", imgpath_);
		}
		std::string imgpath = files[0];
		auto it = image_size.find(imgpath);
		if(it == image_size.end()) {
			ImageCacheEntry img(imgpath.c_str(), 1.0, -1);
			return image_size[imgpath] = img.originalSize();
		}
		return it->second;
	}

	ImageCache& loadImage(const char* imgpath_, double pattern_to_matching) {
		std::string imgpath(imgpath_);
		ImageCache& entry = image_cache[imgpath];
		if(entry.size() > 0) {
			if(entry[0]->scale() == pattern_to_matching) {
				// 既に読み込み済みならそれを返す
				return entry;
			}
			// サイズが違うので再読み込み
			freeImageCache(entry);
		}
		std::vector<std::string> files;
		int idx = 0;
		if(fileList(imgpath_, files)) {
			ImageCacheEntry* image = new ImageCacheEntry(files[0].c_str(), pattern_to_matching, -1);
			entry.push_back(image);
			image_size[imgpath] = image->originalSize();
			++idx;
		}
		for( ; idx < int(files.size()); ++idx) {
			std::string fileName = files[idx];
			size_t last_of_number = fileName.find_last_of(L'.');
			size_t first_of_number = fileName.find_last_of(L'.', last_of_number-1);
			std::string number_str = fileName.substr(
				first_of_number+1, last_of_number-first_of_number-1);
			int number = atoi(number_str.c_str());
			ImageCacheEntry* image = new ImageCacheEntry(fileName.c_str(), pattern_to_matching, number);
			entry.push_back(image);
			image_size[fileName] = image->originalSize();
		}
		if(entry.size() == 0) {
			throw_exception("該当ファイルが１つもありません: %s", imgpath_);
		}
		return entry;
	}

private:
	void freeImageCache(ImageCache& entry) {
		for(ImageCacheEntry* ptr : entry) {
			delete ptr;
		}
		entry.clear();
	}
	bool fileList(const char* imgpath_, std::vector<std::string>& list) {
		std::string imgpath(imgpath_);
		std::string imgpathx = imgpath + "x";
		bool ret = false;
		list.clear();
		// まず imgpath そのままのファイルを読み込む
		std::string* path = &imgpath;
		WIN32_FIND_DATA findData;
		HANDLE findHandle = FindFirstFile(path->c_str(), &findData);
		if(findHandle == INVALID_HANDLE_VALUE) {
			path = &imgpathx;
			findHandle = FindFirstFile(path->c_str(), &findData);
		}
		if(findHandle != INVALID_HANDLE_VALUE) {
			list.push_back(*path);
			FindClose(findHandle);
			ret = true;
		}
		// 連番ファイルを読み込む
		size_t ext_pos = imgpath.find_last_of(L'.');
		if(ext_pos == std::string::npos) {
			throw_exception("ファイルパスに拡張子がありません: %s", imgpath_);
		}
		imgpath.insert(ext_pos, ".*");
		imgpath += "?";
		findHandle = FindFirstFile(imgpath.c_str(), &findData);
		if(findHandle != INVALID_HANDLE_VALUE) {
			utl::StringBuffer<char> string_buf;
			size_t last_splitter = std::max(
				int(imgpath.find_last_of(L'\\')), int(imgpath.find_last_of(L'/')));
			std::string dirPath = imgpath.substr(0, last_splitter+1);
			do {
				string_buf << dirPath << findData.cFileName;
				std::string filePath; string_buf >> filePath;
				list.push_back(filePath);
			} while(FindNextFile(findHandle, &findData));
			FindClose(findHandle);
		}
		return ret;
	}
};

extern AppContext* g_app;

int storeResult(
	const std::vector<SearchResult>& allResult,
	POINT* point,
	int* match_number,
	double* score,
	int max_points)
{
	// 結果を与えられた配列に格納
	int numPoints = std::min((int)allResult.size(), max_points);
	for(int i = 0; i < numPoints; ++i) {
		const SearchResult pt = allResult[i];
		point[i].x = pt.x;
		point[i].y = pt.y;
		score[i] = pt.diff;
		if(match_number) match_number[i] = pt.number;
	}

	return numPoints;
}

int storeResult(
	const std::vector<SearchResult>& allResult,
	int* x,
	int* y,
	int* match_number,
	double* score,
	int max_points)
{
	// 結果を与えられた配列に格納
	int numPoints = std::min((int)allResult.size(), max_points);
	for(int i = 0; i < numPoints; ++i) {
		const SearchResult pt = allResult[i];
		x[i] = pt.x;
		y[i] = pt.y;
		score[i] = pt.diff;
		if(match_number) match_number[i] = pt.number;
	}

	return numPoints;
}

void processResult(
	std::vector<SearchResult>& allResult,
	RECT* rect,
	POINT refSize,
	double matching_scale,
	int num_images,
	int order) // 0: スコア順, 1: 位置順
{
	struct ScoreOrder {
		bool operator()(const SearchResult& r, const SearchResult& l) const {
			return r.diff < l.diff;
		}
	};
	struct PositionOrder {
		bool operator()(const SearchResult& r, const SearchResult& l) const {
			return (r.y != l.y) ? (r.y < l.y) : (r.x < l.x);
		}
	};
	
	// 結果をスコア順にソート
	std::sort(allResult.begin(), allResult.end(), ScoreOrder());
	
	double scale_back = 1.0 / matching_scale;
	int numPoints;

	if(num_images > 1) {
		// テンプレート画像が複数ある場合、重複している箇所はスコアの低い方を削除する
		int rw = refSize.x;
		int rh = refSize.y;
		int w = rect->right - rect->left;
		int h = rect->bottom - rect->top;
		int8_t* filled = new int8_t[w*h]();
		int idx = 0;
		for(int i = 0; i < allResult.size(); ++i) {
			const SearchResult pt = allResult[i];
			if(filled[pt.x + pt.y*w]) {
				// 既にもっと低いスコアがある
				continue;
			}
			// 出力した領域のフラグを立てる
			// 半分までの重なりは許可する
			int lower_x = std::max<int>(0, pt.x - rw/2);
			int lower_y = std::max<int>(0, pt.y - rh/2);
			int upper_x = std::min<int>(w, pt.x + rw/2);
			int upper_y = std::min<int>(h, pt.y + rh/2);
			for(int y = lower_y; y < upper_y; ++y) {
				for(int x = lower_x; x < upper_x; ++x) {
					int offset = x + y * w;
					filled[offset] = true;
				}
			}
			allResult[idx++] = allResult[i];
		}
		allResult.resize(idx, SearchResult());
		delete [] filled;
	}
	
	if(order) {
		std::sort(allResult.begin(), allResult.end(), PositionOrder());
	}
	
	// 座標を戻す
	for(int i = 0; i < (int)allResult.size(); ++i) {
		SearchResult& pt = allResult[i];
		pt.x = pt.x * scale_back + rect->left;
		pt.y = pt.y * scale_back + rect->top;
	}
}

void check_parameters(
	RECT* rect,
	double window_scale,
	double matching_scale, 
	double sad_limit,
	int max_points)
{
	if(rect->bottom <= rect->top || rect->right <= rect->left) {
		throw_exception("指定範囲が有効ではありません: [top,left,bottom,right] = [%d,%d,%d,%d]",
			rect->top, rect->left, rect->bottom, rect->right);
	}
	if(window_scale > 100.0 || window_scale <= 0.0) {
		throw_exception("ウィンドウスケールの数値が異常です: %f", window_scale);
	}
	if(matching_scale > 100.0 || matching_scale <= 0.0) {
		throw_exception("マッチングスケールの数値が異常です: %f", matching_scale);
	}
	if(sad_limit > 100.0 || sad_limit < 0.0) {
		throw_exception("diff_limitの数値が範囲外です: %f", sad_limit);
	}
	if(max_points < 1) {
		throw_exception("max_pointsは１以上を指定してください: %d", max_points);
	}
}

} // chkimg
