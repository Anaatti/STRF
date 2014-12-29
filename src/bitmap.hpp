/** bitmap.hpp **/

#ifndef BITMAP_HPP
#define BITMAP_HPP

#include "global.hpp"

namespace strf {

	class DLL_EXPORT bitmap {
		private:
			bitmap &operator=(const bitmap &map); //Assign operator

		public:
			bitmap(cushort _width, cushort _height, cbool _alpha = true);
			bitmap(cuchar *_data, cushort _width, cushort _height, cbool _alpha = true, cbool _convert_to_alpha = false);
			bitmap(const bitmap &map); //Copy constructor
			~bitmap();
			uchar operator[](cuint pos) const;
			cbool alpha;
			cushort width;
			cushort height;
			cuint size;
			uchar *data;
	};

}

#endif
