/** draw.cpp **/

#include "texture.hpp"
#include "screenshot.hpp"
#include "math.hpp"
#include "init.hpp"
#include <GL/glfw.h>
#include <cmath>

namespace strf {

	extern bool screenshots_initialized;

	double default_aspect = 4.0 / 3.0;
	double default_x1 = 0.0;
	double default_x2 = 4.0 / 3.0;
	double default_y1 = 0.0;
	double default_y2 = 1.0;

	DLL_EXPORT double top_edge = 1.0;
	DLL_EXPORT double bottom_edge = -1.0;
	DLL_EXPORT double left_edge = -1.0;
	DLL_EXPORT double right_edge = 1.0;

	DLL_EXPORT double DLL_CALL res_to_proj_x(cdouble value) {
		//mix(0, resolution->first, left_edge, right_edge, value);
		return (right_edge - left_edge) / (double)resolution->first * value + left_edge;
	}

	DLL_EXPORT double DLL_CALL res_to_proj_y(cdouble value) {
		//mix(0, resolution->second, top_edge, bottom_edge, value);
		return (bottom_edge - top_edge) / (double)resolution->second * value + top_edge;
	}

	DLL_EXPORT double DLL_CALL proj_to_res_x(cdouble value) {
		//mix(left_edge, right_edge, 0, resolution->first, value);
		return (double)resolution->first / (right_edge - left_edge) * (value - left_edge);
	}

	DLL_EXPORT double DLL_CALL proj_to_res_y(cdouble value) {
		//mix(top_edge, bottom_edge, 0, resolution->second, value);
		return (double)resolution->second / (bottom_edge - top_edge) * (value - top_edge);
	}

	inline void update_resolution() {
		if(resizable && resolution) {
			int width, height;
			glfwGetWindowSize(&width, &height);
			if((uint)width != resolution->first) {
				resolution->first = width;
				shader_resolution->first = 2;
				while(shader_resolution->first < (uint)width) shader_resolution->first*= 2;
			}
			if((uint)height != resolution->second) {
				resolution->second = height;
				shader_resolution->second = 2;
				while(shader_resolution->second < (uint)height) shader_resolution->second*= 2;
			}
		}
	}

	DLL_EXPORT void DLL_CALL swap_frame() {
		update_resolution();
		glfwSwapBuffers();
		if(screenshots_initialized) screenshot->handle_screenshots();
	}

	DLL_EXPORT void DLL_CALL poll_events() {
		update_resolution();
		glfwPollEvents();
		if(screenshots_initialized) screenshot->handle_screenshots();
	}

	DLL_EXPORT void DLL_CALL set_default_aspect(cdouble aspect) {
		default_aspect = aspect;
	}

	DLL_EXPORT void DLL_CALL set_projection(cdouble width, cdouble height) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		top_edge = 0;
		bottom_edge = height;
		left_edge = 0;
		right_edge = width;
	}

	DLL_EXPORT void DLL_CALL set_projection(cdouble x1, cdouble y1, cdouble x2, cdouble y2) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(x1, x2, y2, y1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		top_edge = y1;
		bottom_edge = y2;
		left_edge = x1;
		right_edge = x2;
	}

	inline void use_default_projection() {
		if(resolution) {
			cdouble delta_x = default_x2 - default_x1;
			cdouble extra_width = strfmax((delta_x / default_aspect * (double)resolution->first / (double)resolution->second - delta_x) / 2.0, 0.0);
			cdouble delta_y = default_y2 - default_y1;
			cdouble extra_height = strfmax((delta_y * default_aspect / (double)resolution->first * (double)resolution->second - delta_y) / 2.0, 0.0);
			set_projection(default_x1 - extra_width, default_y1 - extra_height, default_x2 + extra_width, default_y2 + extra_height);
		}
		else set_projection(default_x1, default_y1, default_x2, default_y2);
	}

	DLL_EXPORT void DLL_CALL set_default_projection(cdouble width, cdouble height) {
		if(width > 0 && height > 0) {
			default_x1 = 0;
			default_x2 = width;
			default_y1 = 0;
			default_y2 = height;
		}
		use_default_projection();
	}

	DLL_EXPORT void DLL_CALL set_default_projection(cdouble x1, cdouble y1, cdouble x2, cdouble y2) {
		default_x1 = x1;
		default_x2 = x2;
		default_y1 = y1;
		default_y2 = y2;
		use_default_projection();
	}

	DLL_EXPORT void DLL_CALL set_fov(cdouble fov, cdouble aspect, cdouble znear, cdouble zfar) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(fov, aspect, znear, zfar);
		glMatrixMode(GL_MODELVIEW);
	}

	DLL_EXPORT void DLL_CALL look_at(cdouble eyeX, cdouble eyeY, cdouble eyeZ, cdouble centerX, cdouble centerY, cdouble centerZ, cdouble upX, cdouble upY, cdouble upZ) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
	}

	//(x, y) is the upper left corner
	DLL_EXPORT void DLL_CALL draw_box(cfloat x, cfloat y, cfloat width, cfloat height) {
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0, 1.0); glVertex2f(x + width, y);
			glTexCoord2f(0.0, 1.0); glVertex2f(x, y);
			glTexCoord2f(1.0, 0.0); glVertex2f(x + width, y + height);
			glTexCoord2f(0.0, 0.0); glVertex2f(x, y + height);
		glEnd();
	}

	//(x, y) is the middle
	DLL_EXPORT void DLL_CALL draw_rotated_box(cfloat x, cfloat y, cfloat width, cfloat height, cfloat rotation) {
		cfloat half_width = width / 2.0;
		cfloat half_height = height / 2.0;
		cfloat sinx = sin(rotation);
		cfloat cosx = cos(rotation);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0, 1.0); glVertex2f(x + half_height * cosx + half_width * sinx, y + half_height * sinx - half_width * cosx);
			glTexCoord2f(0.0, 1.0); glVertex2f(x - half_height * cosx + half_width * sinx, y - half_height * sinx - half_width * cosx);
			glTexCoord2f(1.0, 0.0); glVertex2f(x + half_height * cosx - half_width * sinx, y + half_height * sinx + half_width * cosx);
			glTexCoord2f(0.0, 0.0); glVertex2f(x - half_height * cosx - half_width * sinx, y - half_height * sinx + half_width * cosx);
		glEnd();
	}

	//(x, y) is the upper left corner
	DLL_EXPORT void DLL_CALL draw_part_box(cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2) {
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(tex_x2, tex_y2); glVertex2f(x + width, y);
				glTexCoord2f(tex_x1, tex_y2); glVertex2f(x, y);
				glTexCoord2f(tex_x2, tex_y1); glVertex2f(x + width, y + height);
				glTexCoord2f(tex_x1, tex_y1); glVertex2f(x, y + height);
			glEnd();
	}

	//(x, y) is the upper left corner
	DLL_EXPORT void DLL_CALL draw_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height) {
		_texture.use();
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0, 1.0); glVertex2f(x + width, y);
			glTexCoord2f(0.0, 1.0); glVertex2f(x, y);
			glTexCoord2f(1.0, 0.0); glVertex2f(x + width, y + height);
			glTexCoord2f(0.0, 0.0); glVertex2f(x, y + height);
		glEnd();
	}	//COPY
		DLL_EXPORT void DLL_CALL draw_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height) {
			_texture->use();
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(1.0, 1.0); glVertex2f(x + width, y);
				glTexCoord2f(0.0, 1.0); glVertex2f(x, y);
				glTexCoord2f(1.0, 0.0); glVertex2f(x + width, y + height);
				glTexCoord2f(0.0, 0.0); glVertex2f(x, y + height);
			glEnd();
		}

	//(x, y) is the middle
	DLL_EXPORT void DLL_CALL draw_rotated_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height, cfloat rotation) {
		cfloat half_width = width / 2.0;
		cfloat half_height = height / 2.0;
		cfloat sinx = sin(rotation);
		cfloat cosx = cos(rotation);
		_texture.use();
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(1.0, 1.0); glVertex2f(x + half_height * cosx + half_width * sinx, y + half_height * sinx - half_width * cosx);
			glTexCoord2f(0.0, 1.0); glVertex2f(x - half_height * cosx + half_width * sinx, y - half_height * sinx - half_width * cosx);
			glTexCoord2f(1.0, 0.0); glVertex2f(x + half_height * cosx - half_width * sinx, y + half_height * sinx + half_width * cosx);
			glTexCoord2f(0.0, 0.0); glVertex2f(x - half_height * cosx - half_width * sinx, y - half_height * sinx + half_width * cosx);
		glEnd();
	}	//COPY
		DLL_EXPORT void DLL_CALL draw_rotated_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height, cfloat rotation) {
			cfloat half_width = width / 2.0;
			cfloat half_height = height / 2.0;
			cfloat sinx = sin(rotation);
			cfloat cosx = cos(rotation);
			_texture->use();
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(1.0, 1.0); glVertex2f(x + half_height * cosx + half_width * sinx, y + half_height * sinx - half_width * cosx);
				glTexCoord2f(0.0, 1.0); glVertex2f(x - half_height * cosx + half_width * sinx, y - half_height * sinx - half_width * cosx);
				glTexCoord2f(1.0, 0.0); glVertex2f(x + half_height * cosx - half_width * sinx, y + half_height * sinx + half_width * cosx);
				glTexCoord2f(0.0, 0.0); glVertex2f(x - half_height * cosx - half_width * sinx, y - half_height * sinx + half_width * cosx);
			glEnd();
		}

	//(x, y) is the upper left corner
	DLL_EXPORT void DLL_CALL draw_part_image(const texture &_texture, cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2) {
			_texture.use();
			glBegin(GL_TRIANGLE_STRIP);
				glTexCoord2f(tex_x2, tex_y2); glVertex2f(x + width, y);
				glTexCoord2f(tex_x1, tex_y2); glVertex2f(x, y);
				glTexCoord2f(tex_x2, tex_y1); glVertex2f(x + width, y + height);
				glTexCoord2f(tex_x1, tex_y1); glVertex2f(x, y + height);
			glEnd();
	}	//COPY
		DLL_EXPORT void DLL_CALL draw_part_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height,
			cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2) {
				_texture->use();
				glBegin(GL_TRIANGLE_STRIP);
					glTexCoord2f(tex_x2, tex_y2); glVertex2f(x + width, y);
					glTexCoord2f(tex_x1, tex_y2); glVertex2f(x, y);
					glTexCoord2f(tex_x2, tex_y1); glVertex2f(x + width, y + height);
					glTexCoord2f(tex_x1, tex_y1); glVertex2f(x, y + height);
				glEnd();
		}

}
