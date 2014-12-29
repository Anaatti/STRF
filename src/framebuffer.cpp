/** framebuffer.cpp **/

#include "init.hpp"
#include "texture.hpp"
#include "math.hpp"
#include "log_ios.hpp"
#include <vector>

namespace strf {

	DLL_EXPORT void DLL_CALL set_projection(cdouble width, cdouble height);
	DLL_EXPORT void DLL_CALL draw_part_image(const texture *_texture, cfloat x, cfloat y, cfloat width, cfloat height,
		cfloat tex_x1, cfloat tex_x2, cfloat tex_y1, cfloat tex_y2);

	std::vector<texture*> *framebuffers;

	bool framebuffers_initialized = false;

	void init_framebuffers() {
		if(init_choise & STRF_INIT_FRAMEBUFFER) {
			framebuffers = new std::vector<texture*>();
			framebuffers_initialized = true;
		}
	}

	void delete_framebuffers() {
		if(framebuffers_initialized) {
			for(std::vector<texture*>::iterator i=framebuffers->begin();i!=framebuffers->end();i++) delete *i;
			delete framebuffers;
			framebuffers_initialized = false;
		}
	}

	inline void push_back_buffer() {
		framebuffers->push_back(new texture());
	}

	DLL_EXPORT void DLL_CALL force_framebuffer_dimensions(cushort width, cushort height) {
		if(shader_resolution && resolution) {
			if(width) shader_resolution->first = width;
			else {
				shader_resolution->first = 2;
				while(shader_resolution->first < resolution->first) shader_resolution->first*= 2;
			}
			if(height) shader_resolution->second = height;
			else {
				shader_resolution->second = 2;
				while(shader_resolution->second < resolution->second) shader_resolution->second*= 2;
			}
		}
	}

	DLL_EXPORT void DLL_CALL save_buffer(cuchar id) {
		if(!framebuffers_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Framebuffers are not initialized" << std::endl;
			return;
		}
		while(id >= framebuffers->size()) push_back_buffer();
		glViewport(0, 0, shader_resolution->first, shader_resolution->second);
		framebuffers->at(id)->use();
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, shader_resolution->first, shader_resolution->second, 0);
		glViewport(0, 0, resolution->first, resolution->second);
	}

	DLL_EXPORT void DLL_CALL draw_buffer(cuchar id, cbool clear) {
		if(!framebuffers_initialized) {
			if(strf_logging) std::cout << "STRF Warning: Framebuffers are not initialized" << std::endl;
			return;
		}
		if(id >= framebuffers->size()) {
			if(strf_logging) std::cout << "STRF Warning: Trying to draw nonexistent framebuffer" << std::endl;
			return;
		}
		if(clear) glClear(GL_COLOR_BUFFER_BIT);
		set_projection(1, 1);
		glViewport(0, 0, strfmin(shader_resolution->first, resolution->first), strfmin(shader_resolution->second, resolution->second));
		draw_part_image(framebuffers->at(id), 0, 0, 1, 1, 0, strfmin((float)resolution->first / (float)shader_resolution->first, 1.0), 0, strfmin((float)resolution->second / (float)shader_resolution->second, 1.0));
		glViewport(0, 0, resolution->first, resolution->second);
	}

	DLL_EXPORT void DLL_CALL redraw_framebuffer(cbool clear) {
		save_buffer(0);
		draw_buffer(0, clear);
	}

}
