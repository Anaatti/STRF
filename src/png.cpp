/** png.cpp **/

#include "bitmap.hpp"
#include "log.hpp"
#include <istream>
#include <sstream>
#include <png.h>

#define PNGSIGSIZE 8

namespace strf {

	void userReadData(png_structp pngPtr, png_bytep data, png_size_t length) {
		png_voidp a = png_get_io_ptr(pngPtr);
		((std::istream*)a)->read((char*)data, length);
	}

	DLL_EXPORT bitmap* DLL_CALL parse_png(cuchar *data, cuint size) {
		std::istringstream file(std::string((cchar*)data, size));

		png_byte pngsig[PNGSIGSIZE];
		file.read((char*)pngsig, PNGSIGSIZE);
		if(!file.good()) return 0;
		if(png_sig_cmp(pngsig, 0, PNGSIGSIZE) != 0) {
			if(strf_logging) log_error << "STRF Error: Not a valid PNG!" << endl;
			return 0;
		}

		png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if(!pngPtr) {
			if(strf_logging) log_error << "STRF Error: Couldn't initialize png read struct" << endl;
			return 0;
		}
		png_infop infoPtr = png_create_info_struct(pngPtr);
		if(!infoPtr) {
			if(strf_logging) log_error << "STRF Error: Couldn't initialize png info struct" << endl;
			png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
			return 0;
		}
		if(setjmp(png_jmpbuf(pngPtr))) {
			png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
			if(strf_logging) log_error << "STRF Error: An error occured while reading the PNG file" << endl;
		}

		png_set_read_fn(pngPtr, (png_voidp)&file, userReadData);

		png_set_sig_bytes(pngPtr, PNGSIGSIZE);
		png_read_info(pngPtr, infoPtr);

		png_uint_32 imgWidth = png_get_image_width(pngPtr, infoPtr);
		png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);
		png_uint_32 bitdepth = png_get_bit_depth(pngPtr, infoPtr);
		png_uint_32 channels = png_get_channels(pngPtr, infoPtr);
		png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

		switch(color_type) {
			case PNG_COLOR_TYPE_PALETTE:
				png_set_palette_to_rgb(pngPtr);
				channels = 3;
				break;
			case PNG_COLOR_TYPE_GRAY:
				if(bitdepth < 8)
				png_set_expand_gray_1_2_4_to_8(pngPtr);
				bitdepth = 8;
				break;
		}
		if(png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
			png_set_tRNS_to_alpha(pngPtr);
			channels+= 1;
		}
		png_bytep* rowPtrs = new png_bytep[imgHeight];
		uchar* pixels = new uchar[imgWidth * imgHeight * bitdepth * channels / 8];
		cuint stride = imgWidth * bitdepth * channels / 8;
		for(size_t i = 0; i < imgHeight; i++) {
			png_uint_32 q = (imgHeight - i - 1) * stride;
			rowPtrs[i] = (png_bytep)pixels + q;
		}
		png_read_image(pngPtr, rowPtrs);

		delete [] (png_bytep)rowPtrs;
		png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);

		bitmap *map = new bitmap(pixels, imgWidth, imgHeight, channels == 4, true);
		delete [] pixels;
		return map;
	}

}
