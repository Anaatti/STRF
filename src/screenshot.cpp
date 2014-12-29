/** screenshot.cpp **/

#include "screenshot.hpp"
#include "init.hpp"
#include "log.hpp"
#include <GL/glfw.h>

namespace strf {

	DLL_EXPORT screenshot_c *screenshot;

	bool screenshots_initialized = false;

	void init_screenshots() {
		if(init_choise & STRF_INIT_SCREENSHOT) {
			screenshot = new screenshot_c;
			screenshots_initialized = true;
		}
	}

	void uninit_screenshots() {
		if(screenshots_initialized) {
			delete screenshot;
			screenshots_initialized = false;
		}
	}

	screenshot_c::screenshot_c():
		width(0),
		height(0),
		half_height(0),
		padding(0),
		state(0),
		took_screenshot(false) {
	}

	screenshot_c::~screenshot_c() {
		finish_saving();
	}

	inline void screenshot_c::put_special(cuint value) {
		//for(uchar i=0;i<4;i++) file.put((value & (255 << (i * 8))) >> (i * 8));
		file.put(value & 0xff);
		file.put((value >> 8) & 0xff);
		file.put((value >> 16) & 0xff);
		file.put(value >> 24);
	}

	//Returns false after saving is complete
	bool screenshot_c::proceed_saving(cint number, cchar *name) {
		try {
			short i = 0;
			switch(state) {
				case 0: //Copy pixel data to memory
					pixels = new uchar[resolution->first * resolution->second * 4];
					glReadPixels(0, 0, resolution->first, resolution->second, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
					width = resolution->first;
					height = resolution->second;
					if(number >= 0) {
						sprintf(filename, "screenshots/%.4i.bmp", number);
						state++;
					}
					else if(name) {
						sprintf(filename, "%s", name);
						state++;
					}
					break;
				case 1: //Get next screenshot file name
					try {
						do {
							temp_file.close();
							sprintf(filename, "screenshots/%.4i.bmp", i);
							temp_file.open(filename);
							i++;
						} while(temp_file.is_open() && i <= 10000);
						temp_file.close();
						if(i > 10000) {
							if(strf_logging) log_error << "STRF Error: Couldn't take a screenshot!" << endl;
							free_resources();
							return false;
						}
					}
					catch(const std::exception &e) {
						if(strf_logging) {
							log_error << "STRF Error: Standard exception while taking a screenshot!" << endl;
							print_exception(e);
						}
						free_resources();
						return false;
					}
					break;
				case 2: //Create a file for screenshot
					try {
						file.open(filename, std::ios::binary);
						if(!file.good()) {
							if(strf_logging) log_error << "STRF Error: Couldn't make a file for a screenshot!" << endl;
							free_resources();
							return false;
						}
					}
					catch(const std::exception &e) {
						if(strf_logging) {
							log_error << "STRF Error: Standard exception while taking a screenshot!" << endl;
							print_exception(e);
						}
						free_resources();
						return false;
					}
					break;
				case 3: //Save bitmap header
					padding = width % 4;
					file.put(66); //B
					file.put(77); //M
					put_special(width * height * 3 + padding * height + 54); //size of the file
					for(uchar i=0;i<4;i++) file.put(0);
					file.put(54); //offset to image data
					for(uchar i=0;i<3;i++) file.put(0);
					file.put(40); //size of this header
					for(uchar i=0;i<3;i++) file.put(0);
					put_special(width); //width of the bitmap
					put_special(height); //height of the bitmap
					file.put(1);
					file.put(0);
					file.put(24); //bits per pixel
					for(uchar i=0;i<5;i++) file.put(0);
					put_special(width * height * 3); //size of the pixel data
					for(uchar i=0;i<16;i++) file.put(0);
					break;
				case 4: //Save the first half of the pixel data
					half_height = height / 2;
					for(uint i=0;i<half_height;i++) {
						for(uint j=0;j<width;j++) {
							cuint pos = (i * width + j) * 4;
							file.put(pixels[pos + 2]);
							file.put(pixels[pos + 1]);
							file.put(pixels[pos]);
						}
						for(uchar j=0;j<padding;j++) file.put(0);
					}
					break;
				case 5: //Save the second half of the pixel data
					for(uint i=half_height;i<height;i++) {
						for(uint j=0;j<width;j++) {
							cuint pos = (i * width + j) * 4;
							file.put(pixels[pos + 2]);
							file.put(pixels[pos + 1]);
							file.put(pixels[pos]);
						}
						for(uchar j=0;j<padding;j++) file.put(0);
					}
					break;
				case 6: //Free resources
					if(strf_logging) log << "STRF: Screenshot '" << filename << "' taken" << endl;
					free_resources();
					return false;
					break;
			}
		}
		catch(const std::exception &e) {
			if(strf_logging) {
				log_error << "STRF Error: Standard exception while taking a screenshot!" << endl;
				print_exception(e);
			}
		}
		state++;
		return true;
	}

	void screenshot_c::finish_saving() {
		if(state) {
			while(proceed_saving()) {};
		}
	}

	void screenshot_c::free_resources() {
		state = 0;
		delete [] pixels;
		file.close();
	}

	//Saves a screenshot as a bitmap image (.bmp)
	void screenshot_c::handle_screenshots() {
		if(state) proceed_saving();
		if(glfwGetKey(GLFW_KEY_F5) || glfwGetKey(GLFW_KEY_F12)) {
			if(!took_screenshot) {
				take_screenshot();
				took_screenshot = true;
			}
		}
		else took_screenshot = false;
	}

	void screenshot_c::take_screenshot(cint number) {
		finish_saving();
		proceed_saving(number);
	}

	void screenshot_c::take_screenshot(cchar *name) {
		finish_saving();
		proceed_saving(-1, name);
	}

}
