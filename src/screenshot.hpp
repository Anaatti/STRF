/** screenshot.hpp **/

#ifndef SCREENSHOT_HPP
#define SCREENSHOT_HPP

#include "global.hpp"
#include <fstream>

namespace strf {

	class DLL_EXPORT screenshot_c {
		private:
			screenshot_c(const screenshot_c &scrn); //Copy constructor
			screenshot_c &operator=(const screenshot_c &scrn); //Assign operator
			void put_special(cuint value);
			bool proceed_saving(cint number = -1, cchar *name = 0);
			void finish_saving();
			void free_resources();
			std::ofstream file;
			std::ifstream temp_file;
			uchar *pixels;
			char filename[100];
			uint width;
			uint height;
			uint half_height;
			uchar padding;
			uchar state;
			bool took_screenshot;

		public:
			screenshot_c();
			~screenshot_c();
			void handle_screenshots();
			void take_screenshot(cint number = -1);
			void take_screenshot(cchar *name);
	};

	extern DLL_EXPORT screenshot_c *screenshot;

}

#endif
