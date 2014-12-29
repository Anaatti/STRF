/** bmp.cpp **/

#include "bitmap.hpp"
#include "log.hpp"

namespace strf {

	DLL_EXPORT bitmap* DLL_CALL parse_bmp(cuchar *data) {
		//Test compatibility
		if(data[30]) {
			if(strf_logging) log_error << "STRF Error: Bitmap compression " << (int)data[30] << " not supported!" << endl;
			return 0;
		}
		cuchar bpp = data[28];
		if(bpp != 16 && bpp != 24 && bpp != 32) {
			if(strf_logging) log_error << "STRF Error: Bitmap format " << (int)bpp << " bits per pixel not supported!" << endl;
			return 0;
		}
		//Dimensions
		cushort width = data[18] + (data[19] << 8) + (data[20] << 16) + (data[21] << 24);
		cushort height = data[22] + (data[23] << 8) + (data[24] << 16) + (data[25] << 24);
		uchar *pixels = new uchar[width * height * 4];
		//Calculate padding
		uint padding = 0;
		if(bpp == 16 && width % 2) padding = 2;
		if(bpp == 24 && width % 4) padding = 4 - (width * 3) % 4;
		//Start of pixel data
		uint count = data[10] + (data[11] << 8) + (data[12] << 16) + (data[13] << 24);
		//Pixel data
		for(ushort i=0;i<height;i++) {
			for(ushort j=0;j<width;j++) {
				cuint pos = (i * width + j) * 4;
				if(bpp == 16) {
					pixels[pos + 2] = uchar(float(data[count] & 31) * 8.23); // 00054321 00000000
					pixels[pos + 1] = uchar(float(((data[count] >> 5) & 7) + ((data[count + 1] << 3) & 24)) * 8.23); // 32100000 00000054
					pixels[pos] = uchar(float((data[count + 1] >> 2) & 31) * 8.23); // 00000000 05432100
					pixels[pos + 3] = 255;//(data[count + 1] & 128) ? 255 : 0; // 00000000 10000000
					count+= 2;
				}
				else {
					pixels[pos + 2] = data[count];
					pixels[pos + 1] = data[count + 1];
					pixels[pos] = data[count + 2];
					if(bpp == 32) {
						pixels[pos + 3] = data[count + 3];
						count+= 4;
					}
					else {
						pixels[pos + 3] = 255;
						count+= 3;
					}
				}
			}
			count+= padding;
		}
		//Create bitmap
		bitmap *map = new bitmap(pixels, width, height);
		delete [] pixels;
		return map;
	}

}
