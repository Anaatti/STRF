/** text.cpp **/

#include "init.hpp"
#include "texture.hpp"
#include "log_ios.hpp"
#include <cstdio>
#include <cstring>

namespace strf {

	DLL_EXPORT texture *font[256];

	bool font_initialized = false;

	void init_font();

	void load_font() {
		if(init_choise & STRF_INIT_FONT) {
			init_font();
			font_initialized = true;
		}
	}

	void delete_font() {
		if(font_initialized) {
			for(ushort i=0;i<256;i++) {
				delete font[i];
				font[i] = 0;
			}
			font_initialized = false;
		}
	}

	float text_scale = 1.0;
	float text_spacing = 0.56; //Gained from underscore (us len / img len: 36 / 64)

	DLL_EXPORT void DLL_CALL set_text_scale(cfloat scale) {
		text_scale = scale;
	}

	DLL_EXPORT void DLL_CALL set_text_spacing(cfloat spacing) {
		text_spacing = spacing * 0.56;
	}

	//size is y-size
	DLL_EXPORT void DLL_CALL draw_text(cchar *text, cfloat x, cfloat y, cfloat size, cuchar align) {
		if(!font_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Text is not initialized" << std::endl;
			return;
		}
		cfloat xsize = size * text_scale;
		cfloat posx = x - (float(strlen(text) - 1) * text_spacing * size + xsize) * (align == 0 ? 0 : (align == 1 ? 0.5 : 1.0));
		short i = 0;
		while(text[i]) {
			cfloat posx2 = posx + (float)i * text_spacing * size;
			font[(uchar)text[i]]->use();
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(0.0, 0.0);
					glVertex2f(posx2, y + size);
				glTexCoord2f(1.0, 0.0);
					glVertex2f(posx2 + xsize, y + size);
				glTexCoord2f(0.0, 1.0);
					glVertex2f(posx2, y);
				glTexCoord2f(1.0, 1.0);
					glVertex2f(posx2 + xsize, y);
			glEnd();
			i++;
		}
	}

	DLL_EXPORT void DLL_CALL draw_char(cchar c, cfloat x, cfloat y, cfloat size, cuchar align) {
		if(!font_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Text is not initialized" << std::endl;
			return;
		}
		cfloat xsize = size * text_scale;
		cfloat posx = x - xsize * (align == 0 ? 0 : (align == 1 ? 0.5 : 1.0));
		font[(uchar)c]->use();
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0, 0.0);
				glVertex2f(posx, y + size);
			glTexCoord2f(1.0, 0.0);
				glVertex2f(posx + xsize, y + size);
			glTexCoord2f(0.0, 1.0);
				glVertex2f(posx, y);
			glTexCoord2f(1.0, 1.0);
				glVertex2f(posx + xsize, y);
		glEnd();
	}

	DLL_EXPORT void DLL_CALL draw_vertical_text(cchar *text, cfloat x, cfloat y, cfloat size, cuchar align) {
		if(!font_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Text is not initialized" << std::endl;
			return;
		}
		cfloat xsize = size * text_scale;
		cfloat posy = y + (float(strlen(text) - 1) * text_spacing * size + xsize) * (align == 0 ? 0 : (align == 1 ? 0.5 : 1.0));
		short i = 0;
		while(text[i]) {
			cfloat posy2 = posy - (float)i * text_spacing * size;
			font[(uchar)text[i]]->use();
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(0.0, 0.0);
					glVertex2f(x + size, posy2);
				glTexCoord2f(1.0, 0.0);
					glVertex2f(x + size, posy2 - xsize);
				glTexCoord2f(0.0, 1.0);
					glVertex2f(x, posy2);
				glTexCoord2f(1.0, 1.0);
					glVertex2f(x, posy2 - xsize);
			glEnd();
			i++;
		}
	}

	DLL_EXPORT void DLL_CALL draw_int(cint value, cfloat x, cfloat y, cfloat size, cuchar align) {
		if(!font_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Text is not initialized" << std::endl;
			return;
		}
		char number[12];
		sprintf(number, "%i", value);
		draw_text(number, x, y, size, align);
	}

	DLL_EXPORT void DLL_CALL draw_float(cfloat value, cuchar precision, cfloat x, cfloat y, cfloat size, cuchar align) {
		if(!font_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Text is not initialized" << std::endl;
			return;
		}
		else if(precision > 9) {
			if(strf_logging) std::cout << "STRF Warning: Precision for float printing is too high" << std::endl;
			return;
		}
		char number[20];
		char temp[5] = "%.0f";
		temp[2] = precision + '0';
		sprintf(number, temp, value);
		draw_text(number, x, y, size, align);
	}

}
