/** bitmap.cpp **/

#include "bitmap.hpp"
#include <cstring>

namespace strf {

	bitmap::bitmap(cushort _width, cushort _height, cbool _alpha):
		alpha(_alpha),
		width(_width),
		height(_height),
		size(width * height * (alpha ? 4 : 3)),
		data(new uchar[size]) {
	}

	bitmap::bitmap(cuchar *_data, cushort _width, cushort _height, cbool _alpha, cbool _convert_to_alpha):
		alpha(_convert_to_alpha ? true : _alpha),
		width(_width),
		height(_height),
		size(width * height * (alpha ? 4 : 3)),
		data(new uchar[size]) {
		if(!_alpha && alpha) {
			for(int i = 0; i < width * height; i++) {
				data[i * 4    ] = _data[i * 3    ];
				data[i * 4 + 1] = _data[i * 3 + 1];
				data[i * 4 + 2] = _data[i * 3 + 2];
				data[i * 4 + 3] = 255;
			}
		}
		else memcpy(data, _data, size);
	}

	bitmap::bitmap(const bitmap &map):
		alpha(map.alpha),
		width(map.width),
		height(map.height),
		size(width * height * (alpha ? 4 : 3)),
		data(new uchar[size]) {
		memcpy(data, map.data, size);
	}

	bitmap::~bitmap() {
		delete [] data;
	}

	//Stuff out of bounds is transparent black
	uchar bitmap::operator[](cuint pos) const {
		if(pos >= size) return 0;
		else return data[pos];
	}

}
